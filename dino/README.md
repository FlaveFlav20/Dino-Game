# Dino

## Structure

- **dinoBackend**: the backend. See **dinoBackend/README.md**
- **src**: source files
    - **src/Includes**: Includes files
        - **src/Includes/Dino.h**: Our dino game. With the **Setup** structure
    - **src/Dino.c**: Our game

## Explaination setup

- **in_**: a stream/file to get input (like sys.stdin)
- **file_out**: a stream/file to display result (like sys.stdout)
- **time_between_frames**: the time between 2 frame in 5 * 100 ms
- **chance**: it must be more than 4. Higher the chance is, lesser there are harmful entity (but be careful, the chance decrease by 1 between frame)
- **min_chance**: minimum chance. It musb be more than 4
- **dino_jump_height**: the jump height
- **display_rows**: the length of the result
- **display_cols**: the height of the result
- **display_ground_height**: the height of the ground
