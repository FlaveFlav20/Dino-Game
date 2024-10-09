#include "../src/Includes/Dino.h"

int main()
{
    struct Setup setup = {
        .server_out = stdout,
        .in_ = stdin,
        .time_between_frame_ns = 5,
        .chance = 100,
        .min_chance = 10,
        .dino_jump_height = 5,
        .display_rows = 100,
        .display_cols = 10,
        .display_ground_height= 1
    };

    start_dino(&setup);
}
