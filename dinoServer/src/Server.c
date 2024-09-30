#include "Includes/Server.h"

#include "Includes/Display.h"
#include "Includes/Utils.h"

#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <termio.h>

#include<signal.h> 

bool run = true;

void handle_sigterm(int sig) 
{ 
    run = false;
    printf("Heuuuuuuu SIGTEEEEEERM\n");
} 

static void enable_raw_mode(FILE *file)
{

    int fd = fileno(file);
    struct termios tty;

    tcgetattr(fd, &tty);

    tty.c_lflag &= ~(ICANON | ECHO);

    tty.c_cc[VMIN] = 1;

    tty.c_cc[VTIME] = 0;

    tcsetattr(fd, TCSANOW, &tty);

    fcntl(fd, F_SETFL, O_NONBLOCK);
}

void disable_raw_mode(FILE *file)
{
    int fd = fileno(file);
    struct termios tty;

    tcgetattr(fd, &tty);

    tty.c_lflag |= (ICANON | ECHO);
    tcsetattr(fd, TCSANOW, &tty);
}

bool init_server(struct Server *server)
{
    if (!server)
        return false;

    signal(SIGTERM, handle_sigterm); 
    struct Elements *elements = init_Elems(server->display, server->jump_height);

    enable_raw_mode(server->in);

    char buffer[] = "          ";

    struct timespec req;
    req.tv_sec = 0;
    req.tv_nsec = server->time_between_frame_ns;

    ssize_t chance = server->chance;

    do 
    {
        ssize_t counter = 0;
        while (nanosleep(&req, NULL) == -1 && counter < 100)
        {
            counter++;
            printf("Hahahahah %ld\n", req.tv_nsec);
        }
        screen_display(server->display, server->out, elements);

        ssize_t size = fread(buffer, sizeof(char), 10, server->in);

        struct Input input = parse_input(buffer, size);

        move_dino(elements, input.jump, input.shift);
        if (chance > server->min_chance)
            chance--;
        
        ssize_t clear = 0;
        while ((clear = fread(buffer, sizeof(char), 10, server->in)) > 0)
            clear = 0;
    } while (next_frame_Elems(elements, chance) == ALIVE && run);

    disable_raw_mode(server->in);

    free_Elems(elements);
    return true;
}

struct Input parse_input(char *buffer, ssize_t buffer_size)
{
    struct Input input =
    {
        .jump = false,
        .shift = false,
    };

    if (buffer == NULL)
        return input;

    for (ssize_t i = 0; i < buffer_size; i++)
    {
        if (buffer[i] == ' ')
            input.jump = true;
        else if (buffer[i] == 'c')
            input.shift = true;
    }
    return input;
}
