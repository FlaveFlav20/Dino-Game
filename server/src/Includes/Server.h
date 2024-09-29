#ifndef SERVER_H
#define SERVER_H

#include "Display.h"

#include <stdio.h>
#include <stdbool.h>
#include <sys/types.h>

struct Server
{
    struct Display *display;
    FILE* in;
    FILE* out;
    ssize_t time_between_frame_ns;
    ssize_t chance;
    ssize_t min_chance;
    ssize_t jump_height;
};

struct Input
{
    bool jump;
    bool shift;
};

bool init_server(struct Server *server);
struct Input parse_input(char *buffer, ssize_t buffer_size);

#endif // SERVER_H
