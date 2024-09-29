#ifndef UTILS_H
#define UTILS_H

#include "Entities.h"
#include "Display.h"

#include <stdbool.h>
#include <sys/types.h>

#define NUMBER_ELEMENTS 30

struct Element
{
    struct Element *next;
    ssize_t x;
    ssize_t y;
    enum ENTITIES entity;
};

struct Dino
{
    ssize_t x;
    ssize_t y;
    bool shift;
    ssize_t height_jump;
    bool is_jumping;
};

struct Elements
{
    struct Display *display;
    struct Element *element;
    struct Dino *dino;
};

enum STATE
{
    ALIVE,
    DEAD,
    ERROR,
};

struct Elements *init_Elems(struct Display *display, ssize_t jump);

bool free_Elems(struct Elements *elements);

enum STATE next_frame_Elems(struct Elements *elements, ssize_t chance);

enum ENTITIES get_entity(struct Elements *elements, ssize_t x, ssize_t y);

bool move_dino(struct Elements *elements, bool jump, bool shift);

#endif // UTILS_H
