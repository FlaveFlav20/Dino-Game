## Dino Game

## Table of Contents

-[Intro](#Intro)
-[How to create libs?](#How-to-create-libs)
-[Structure](#Structure)

## Intro

This is a dino game coded in C. It's working via a server which deals with all events, and a client which send inputs, and receive a screen.

## How-to-create-libs

- C lib

``sh
make lib
```

- Python lib

You should use a python environement with

```sh
python3 -m venv env
```

Then, you can use it with

```sh
source env/bin/activate
```

Then, you can creta python lib (you must know your sudo password)

```sh
sh create_python_lib.sh
```

Then, you can use the lib (see **python/README.md**)

## Structure

- **Dino-game**: The server. See **Dino-game/README.md**
- **python**: It allows to create the python library. See **python/README.md**
- **src**: Sources files
    - **src/Includes**: All headers
    - **src/Includes/Dino.h**
    - **src/Dino.c**
- **Makefile**: make lib/ make test
- **README.md**: This file :D
- **test.c**: Test with C code
- **test.py**: Test with python code