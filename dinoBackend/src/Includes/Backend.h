#ifndef SERVER_H
#define SERVER_H

#include "Display.h"

#include <stdio.h>
#include <stdbool.h>
#include <sys/types.h>

/*
    struct Backend:
        - display: see Display.h
        - FILE * :
            - in: to get input (like stdin)
            - out: to display result (like stdout)
        - time_between_frame_ns: explicit name... no?
        - chance: Higher the chance is, lesser there are harmful entity (but be careful, the chance decrease by 1 between frame). => To know more, see Utils.c/h
        - min_chance: the chance can't decrease under this value
        - jump_height: this is for the dino
*/

struct Backend
{
    struct Display *display;
    FILE* in;
    FILE* out;
    ssize_t time_between_frame_ns;
    ssize_t chance;
    ssize_t min_chance;
    ssize_t jump_height;
};

/*
    struct Input: A temporary struct to get input for the dino
*/

struct Input
{
    bool jump;
    bool shift;
};

/*
    init_server: To launch the server
        - return value: false if error, true else
*/

bool init_backend(struct Backend *backend);

/*
    parse_input: To know whare are the input of the buffer. It will take the last input from the buffer for jump and shift
*/

struct Input parse_input(char *buffer, ssize_t buffer_size);

#endif // SERVER_H
