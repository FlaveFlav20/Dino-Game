#include "Includes/Backend.h"

#include "Includes/Display.h"
#include "Includes/Utils.h"

#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <termio.h>
#include <errno.h>

#include <signal.h>

bool run = true;

void handle_sigterm(int sig) {
    run = false;
}

/*static void enable_raw_mode(FILE *file)
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
}*/

bool init_backend(struct Backend *backend)
{
    if (!backend)
        return false;

    struct sigaction action;
    action.sa_handler = handle_sigterm;
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;  // No flags

    // Set the handler for SIGTERM
    if (sigaction(SIGTERM, &action, NULL) < 0) {
        perror("sigaction");
        return 1;
    }

    struct Elements *elements = init_Elems(backend->display, backend->jump_height);

    //enable_raw_mode(backend->in);

    struct timespec req;
    req.tv_sec = 0;
    req.tv_nsec = backend->time_between_frame_ns;

    ssize_t chance = backend->chance;

    do 
    {
        ssize_t counter = 0;
        int err = 0;
        while ((err = nanosleep(&req, NULL)) == -1 && counter < 100)
        {
            counter++;
            if (errno == EINTR) {
                fprintf(stderr, "nanosleep interrupted: %ld seconds left\n", req.tv_sec);
            } else {
                perror("nanosleep failed");
            }
        }
        screen_display_(backend->display, backend->out, elements);

        char buffer[11] = { '\0' };
        ssize_t size = fread(buffer, sizeof(char), 10, backend->in);

        struct Input input = parse_input(buffer, size);

        move_dino(elements, input.jump, input.shift);
        if (chance > backend->min_chance)
            chance--;
        
        ssize_t clear = 0;
        while ((clear = fread(buffer, sizeof(char), 10, backend->in)) > 0)
            clear = 0;
    } while (next_frame_Elems(elements, chance) == ALIVE && run);

    //disable_raw_mode(backend->in);

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
        {
            input.jump = true;
        }
        else if (buffer[i] == 'c')
            input.shift = true;
    }
    return input;
}
