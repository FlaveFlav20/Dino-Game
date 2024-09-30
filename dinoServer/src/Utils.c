#include "Includes/Utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Elements *init_Elems(struct Display *display, ssize_t jump)
{
    if (!display)
        return NULL;

    struct Elements *res = malloc(sizeof(struct Elements));
    if (!res)
        return NULL;

    res->display = display;
    res->element = NULL;
    res->number_entities = 0;

    struct Dino *dino = malloc(sizeof(struct Dino));
    if (!dino)
    {
        free_Elems(res);
        return NULL;
    }

    dino->shift = false;
    dino->x = 1;
    dino->y = display->ground_height + 1;
    dino->height_jump = jump;
    dino->is_jumping = false;

    res->dino = dino;

    return res;
}

static void free_elem(struct Element *element)
{
    if (!element)
        return;
    free_elem(element->next);
    free(element);
}

bool free_Elems(struct Elements *elements)
{
    if (!elements)
        return false;

    free_elem(elements->element);
    free(elements->dino);
    free(elements);

    return true;
}

static bool append_Elem(struct Elements *elements, ssize_t x, ssize_t y, enum ENTITIES entity)
{
    if (!elements)
        return false;

    struct Element *new_element = malloc(sizeof(struct Element));
    if (!new_element)
        return false;

    new_element->next = NULL;
    new_element->x = x;
    new_element->y = y;
    new_element->entity = entity;

    if (!elements->element)
        elements->element = new_element;
    else
    {
        struct Element *e = elements->element;
        while (e->next)
            e = e->next;

        e->next = new_element;
    }
    elements->number_entities++;
    return true;
}

static bool remove_Elem(struct Elements *elements, struct Element *to_remove)
{
    if (!elements || !elements->element || !to_remove)
        return false;

    if (elements->element == to_remove)
    {
        elements->element = elements->element->next;
        free(to_remove);
        elements->number_entities--;
        return true;
    }

    struct Element *e = elements->element;

    while (!e)
    {
        if (e->next == to_remove)
        {
            e->next = e->next->next;
            free(to_remove);
            return true;
        }
    }
    return false;
}

/*
    shift_Elem: It's moving all BIRDS/BUSHES and they will be remove when we don't need them anymore
        - return: DINO state
*/

enum STATE shift_Elem(struct Elements *elements)
{
    if (!elements)
        return ERROR;
    struct Element *e = elements->element;

    bool alive = true;

    while (e)
    {
        if (e->entity != DINO &&
            elements->dino->x == e->x && (elements->dino->y == e->y 
                                            || (!elements->dino->shift && (elements->dino->y + 1) == e->y)))
        {
            alive = false;
        }

        if (e->entity == DINO)
        {
            e = e->next;
        }
        else if (e->x == 0)
        {
            struct Element *temp = e;
            e = e->next;
            remove_Elem(elements, temp);
        }
        else
        {
            e->x--;
            e = e->next;
        }


    }
    if (alive)
        return ALIVE;
    return DEAD;
}


enum STATE next_frame_Elems(struct Elements *elements, ssize_t chance)
{
    enum STATE state = shift_Elem(elements);
    if (state == ERROR)
        return ERROR;
    else if (state == DEAD)
        return DEAD;

    // Choose a random entity

    struct timespec ts;

    if (clock_gettime(CLOCK_REALTIME, &ts) == -1)
        return ERROR;

    printf("%ld %ld\n", elements->number_entities, (int)elements->display->rows / elements->display->cols);

    if (elements->number_entities >= (elements->display->rows / elements->display->cols))
        return ALIVE;

    printf("Heu");

    srand(ts.tv_sec * 1000 + ts.tv_nsec);
    ssize_t r = ((ssize_t)rand()) % chance;

    // Add this new entity

    if (r > 1)
        return ALIVE;
    else if (r == BUSH)
    {
        append_Elem(elements, elements->display->rows - 1, elements->display->ground_height + 1, (enum ENTITIES)r);
        return ALIVE;
    }

    // Only birds cqn be here

    if (clock_gettime(CLOCK_REALTIME, &ts) == -1)
        return ERROR;

    // To choose the bird height

    srand(ts.tv_sec * 1000 + ts.tv_nsec);
    ssize_t y = ((ssize_t)rand()) % 3;

    if (!append_Elem(elements, elements->display->rows - 1, y + elements->display->ground_height + 1, (enum ENTITIES)r))
        return ERROR;
    return ALIVE;
}

enum ENTITIES get_entity(struct Elements *elements, ssize_t x, ssize_t y)
{
    if (!elements || !elements->dino)
        return NONE;

    if ((elements->dino->x == x) && ((elements->dino->y == y)
                                    || (!elements->dino->shift && (elements->dino->y + 1 == y))))
        return DINO;

    struct Element *e = elements->element;

    while (e)
    {
        if (e->x == x && e->y == y)
            return e->entity;
        e = e->next;
    }
    return NONE;
}

bool move_dino(struct Elements *elements, bool jump, bool shift)
{
    if (!elements || !elements->dino)
        return false;
    
    if (elements->dino->y == elements->display->ground_height + 1 && jump)
    {
        /*
            DINO on ground
            DINO->is_jumping = true/false
            INPUT = {jumping = true, shift = true/false}
        */
        elements->dino->y++;
        elements->dino->is_jumping = true;
        elements->dino->shift = false;
    }
    else if (elements->dino->y == elements->display->ground_height + 1 && shift)
    {
        /*
            DINO on ground
            DINO->is_jumping = true/false
            INPUT = {jumping = false, shift = true}
        */
        elements->dino->is_jumping = false;
        elements->dino->shift = true;
    }
    else if (elements->dino->y == (elements->dino->height_jump + elements->display->ground_height + 1))
    {
        /*
            DINO not on ground and DINO->y == DINO->jump_height
            DINO->is_jumping = true/false
            INPUT = {jumping = true/false, shift = true/false}
        */
        elements->dino->is_jumping = false;
        elements->dino->y--;
    }
    else if ((elements->dino->y != elements->display->ground_height + 1) 
            && elements->dino->y > elements->display->ground_height && elements->dino->is_jumping)
    {
        /*
            DINO not on ground
            DINO->is_jumping = true
            INPUT = {jumping = true/false, shift = true/false}
        */
        elements->dino->y++;
    }
    else if ((elements->dino->y != elements->display->ground_height + 1) 
            && elements->dino->y > elements->display->ground_height && !elements->dino->is_jumping)
    {
        /*
            DINO not on ground
            DINO->is_jumping = true
            INPUT = {jumping = true/false, shift = true/false}
        */
        elements->dino->y--;
    }
    else 
        elements->dino->shift = false;
    return true;
}