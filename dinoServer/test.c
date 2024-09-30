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
        .time_between_frame_ns = 5 * 100000000L,
        .chance = 4,
        .min_chance = 4,
        .jump_height = 4
    };

    init_server(&server);

}
