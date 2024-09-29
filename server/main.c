#include "src/Includes/Display.h"
#include "src/Includes/Server.h"

int main(int argc, char **argv)
{
    if (argc < 0)
        return 1;

    struct Display  display = {
        .rows = 100,
        .cols = 15,
        .ground_height = 3
    };

    struct Server server =
    {
        .display = &display,
        .in = stdin,
        .out = stdout,
        .time_between_frame_ns = 500000000,
        .chance = 50,
        .min_chance = 10,
        .jump_height = 4
    };


    init_server(&server);

}
