#ifndef DISPLAY_H
#define DISPLAY_H

#include "Utils.h"

#include <stdio.h>
#include <stdbool.h>
#include <sys/types.h>

struct Elements;

/*
            rows
         <--------->
        |           |   ^
        |           |   |   cols
        |           |   v
        #############   ^
        #############   |   ground_height
        #############   v
*/

struct Display
{
    ssize_t rows;
    ssize_t cols;
    ssize_t ground_height;
};

bool screen_display_(struct Display *display, FILE *stream, struct Elements *elements);

#endif // DISPLAY_H
