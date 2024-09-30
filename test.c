#include "src/Includes/Dino.h"

int main()
{
    FILE *server_in = fopen("server_in", "rw");
    struct Setup setup = {
        .server_in = server_in,
        .server_out = stdout,
        .in = stdin,
        .time_between_frame_ns = 1000 * 1000000L,
        .chance = 100,
        .min_chance = 10,
        .dino_jump_height = 4,
        .display_rows = 30,
        .display_cols = 10,
        .display_ground_height= 1
    };

    start_dino(&setup);
    fclose(server_in);
}