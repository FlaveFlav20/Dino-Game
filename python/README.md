# Dino

## Table of Contents

- [Class](#Class)
- [Explaination](#Explaination)
- [Example](#Example)
- [Structures](#Structures)

## Class

```py
class Dino:
    def __init__(self, fd_in: int, fd_out: int, 
                time_between_frames: int,
                chance: int, min_chance: int, 
                dino_jump_height: int,
                display_rows: int, display_cols: int, display_ground_height: int) -> None:
        ...

    def start(self) -> bool:
        ...
```

## Explaination

- **in_**: a stream/file to get input (like sys.stdin)
- **file_out**: a stream/file to display result (like sys.stdout)
- **time_between_frames**: the time between 2 frame in 5 * 100 ms
- **chance**: it must be more than 4. Higher the chance is, lesser there are harmful entity (but be careful, the chance decrease by 1 between frame)
- **min_chance**: minimum chance. It musb be more than 4
- **dino_jump_height**: the jump height
- **display_rows**: the length of the result
- **display_cols**: the height of the result
- **display_ground_height**: the height of the ground

## Example

```py
import sys
import dino

#Init
dino = dino.Dino(fd_in=sys.stdin.fileno(), fd_out=sys.stdout.fileno(),
                    time_between_frames=5,
                    chance=30, min_chance=10,
                    dino_jump_height=4, 
                    display_rows=50, display_cols=8, display_ground_height=2)
# Start
dino.start()
```

## Structures

- **create.sh**: To create the python lib
- **clean.sh**: To remove all trash files
- **dino**: the module
    - **dino/__init__.py**: our module
- **setup.py**: It allows to create the library with pip