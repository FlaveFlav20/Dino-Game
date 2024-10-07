#ifndef DINO_H
#define DINO_H

#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>

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