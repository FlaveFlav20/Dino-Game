#include "Includes/Display.h"
#include "Includes/Entities.h"

#include <stdio.h>

/*
    array_char: It will use the enum (BUSH=0, BIRD=1, DINO=2...) to displaye the right character
*/  

char *array_char = "%v$E";

static void draw_one_line(struct Display *display, FILE *stream)
{
    fwrite("|", sizeof(char), 1, stream);
    for (ssize_t i = 0; i < display->rows; i++)
        fwrite("~", sizeof(char), 1, stream);
    fwrite("|\n", sizeof(char), 2, stream);
}

bool screen_display_(struct Display *display, FILE *stream, struct Elements *elements)
{
    if (!display || !stream || !elements)
        return false;
    draw_one_line(display, stream);
    for (ssize_t y = display->cols; y != 0; y--)
    {
        fwrite("|", sizeof(char), 1, stream);
        for (ssize_t x = 0; x < display->rows; x++)
        {
            enum ENTITIES entity = get_entity(elements, x, y);
            if (entity != NONE)
            {
                char *addr = &(array_char[entity]);
                fwrite(addr, sizeof(char), 1, stream);
            }
            else if (y > display->ground_height)
            {
                fwrite(" ", sizeof(char), 1, stream);
            }
            else
            {
                fwrite("#", sizeof(char), 1, stream);
            }
        }
        fwrite("|\n", sizeof(char), 2, stream);
    }

    draw_one_line(display, stream);
    fflush(stream);
    fflush(stdout);
    return true;
}
