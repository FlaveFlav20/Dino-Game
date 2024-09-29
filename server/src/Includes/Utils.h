#ifndef UTILS_H
#define UTILS_H

#include "Entities.h"
#include "Display.h"

#include <stdbool.h>
#include <sys/types.h>

#define NUMBER_ELEMENTS 30

/*
    struct Element: struct for bird/bush entity
        - next: it's a linked list
        - x/y: coordinate
        - entity: BIRD or BUSH
*/

struct Element
{
    struct Element *next;
    ssize_t x;
    ssize_t y;
    enum ENTITIES entity;
};

/*
    struct Dino:
        - x/y: coordinate
        - shift: because dino can shift to deal with birds
        - height_jump: number of jumping char
        - is_jumping: to know if we go down or up while dino not on ground
*/

struct Dino
{
    ssize_t x;
    ssize_t y;
    bool shift;
    ssize_t height_jump;
    bool is_jumping;
};

/*
    struct Elements: The main struct
        - display: to display xD
        - element: it's like a linked list for BUSH and BIRD entities
        - dino: you :)
*/

struct Elements
{
    struct Display *display;
    struct Element *element;
    struct Dino *dino;
};

/*
    enum STATE: DINO state
*/

enum STATE
{
    ALIVE,
    DEAD,
    ERROR,
};

/*
    init_Elems + init_Elems: just to have dynamic memory
*/

struct Elements *init_Elems(struct Display *display, ssize_t jump);

bool free_Elems(struct Elements *elements);

/*
    get_entity: display will use it to know if there is an entity to show
*/

enum ENTITIES get_entity(struct Elements *elements, ssize_t x, ssize_t y);

/*
    next_frame_Elems: it's making entity to move, and dino to change state (if he's dead for example)
        - chance: see Utils.c
*/

enum STATE next_frame_Elems(struct Elements *elements, ssize_t chance);

/*
    move_dino: it's dealing with dino movement and inut. It will choose the right action
    It muste be called before next_frame_Elems;
*/

bool move_dino(struct Elements *elements, bool jump, bool shift);

#endif // UTILS_H
