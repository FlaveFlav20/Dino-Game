#include "Includes/Client.h"

#include <stdio.h>

bool client_get_input(void)
{
    while (1)
    {
        char buff[] = { '\0', '\n', '\0'};
        int check = fread(buff, sizeof(char), 1, stdin);
        if (check == -1)
            return false;
        if (!check)
            continue;

        fwrite(buff, sizeof(char), 2, stdout);
    }
    return true;
}
