## Dino

# Class

```py
class Dino:
    def __init__(self, file_in: typing.IO, file_out: typing.IO, time_between_frames: int,
                chance: int, min_chance: int, dino_jump_height: int,
                display_rows: int, display_cols: int, display_ground_height: int):
        ...

    def start(self) -> bool:
        ...
```

# Explaination

- **file_in**: a stream/file to get input (like sys.stdin)
- **file_out**: a stream/file to display result (like sys.stdout)
- **time_between_frames**: the time between 2 frame in 5 * 100 ms
- **chance**: it must be more than 4. Higher the chance is, lesser there are harmful entity (but be careful, the chance decrease by 1 between frame)
- **min_chance**: minimum chance. It musb be more than 4
- **dino_jump_height**: the jump height
- **display_rows**: the length of the result
- **display_cols**: the height of the result
- **display_ground_height**: the height of the ground

# Example

```py
import sys
import dino

#Init
dino = dino.Dino(file_in=sys.stdin, file_out=sys.stdout, time_between_frames=5 * 100000000, 
                    chance=100, min_chance=10, dino_jump_height=4, display_rows=25, 
                    display_cols=8, display_ground_height=2)
# Start
dino.start()
```