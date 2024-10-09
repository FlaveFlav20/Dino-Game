#ifndef DINO_H
#define DINO_H

#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>

/*
- **in_**: a stream/file to get input (like sys.stdin)
- **file_out**: a stream/file to display result (like sys.stdout)
- **time_between_frames**: the time between 2 frame in 5 * 100 ms
- **chance**: it must be more than 4. Higher the chance is, lesser there are harmful entity (but be careful, the chance decrease by 1 between frame)
- **min_chance**: minimum chance. It musb be more than 4
- **dino_jump_height**: the jump height
- **display_rows**: the length of the result
- **display_cols**: the height of the result
- **display_ground_height**: the height of the ground
*/

struct Setup
{
    int server_out;
    int in_;
    ssize_t time_between_frame_ns;
    ssize_t chance;
    ssize_t min_chance;
    ssize_t dino_jump_height;
    ssize_t display_rows;
    ssize_t display_cols;
    ssize_t display_ground_height;
};

bool start_dino(struct Setup *setup);

#endif // DINO_H