#include "Includes/Server.h"

#include "Includes/Display.h"
#include "Includes/Utils.h"

#include <unistd.h>
#include <fcntl.h>
#include <time.h>
// To do: jump size

bool init_server(struct Server *server)
{
    if (!server)
        return false;
    struct Elements *elements = init_Elems(server->display, server->jump_height);

    int fd = fileno(server->in);
    fcntl(fd, F_SETFL, O_NONBLOCK);
    char buffer[] = "          ";

    struct timespec req = {0, server->time_between_frame_ns};

    ssize_t chance = server->chance;

    do 
    {
        nanosleep(&req, NULL);
        screen_display(server->display, server->out, elements);

        ssize_t size = fread(buffer, sizeof(char), 10, server->in);

        struct Input input = parse_input(buffer, size);

        move_dino(elements, input.jump, input.shift);
        if (chance > server->min_chance)
            chance--;
        
        ssize_t clear = 0;
        while ((clear = fread(buffer, sizeof(char), 10, server->in)) > 0)
            clear = 0;
    } while (next_frame_Elems(elements, chance) == ALIVE);

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
