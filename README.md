## Dino Game

## Table of Contents

- [Intro](#Intro)
- [How to create libs?](#How-to-create-libs)
- [Why should we use sudo to create the lib?](#Why-should-we-use-sudo-to-create-the-lib)
- [Structure](#Structure)
- [Example-of-1-output-frame](#Example-of-1-output-frame)
- [How to control dino?](#How-to-control-dino)

## Intro

This is a dino game coded in C. It's working via a server which deals with all events, and a client which send inputs, and receive a screen.

## How-to-create-libs

- C lib

```sh
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

## Why-should-we-use-sudo-to-create-the-lib
We must put the library **.so** into **/usr/lib** to avoid hardcoded path

If you can't or won't use sudo, you should modify the path in **python/dino/__init__.py** from this line
```py
blackboxLib = ctypes.CDLL("/usr/lib/libdino.so")
```
to 
```py
blackboxLib = ctypes.CDLL("your_absolute_path_to_libdino/libdino.so")
```

## Structure

- **DinoBackend**: The backend. See **DinoBackend/README.md**
- **python**: It allows to create the python library. See **python/README.md**
- **src**: Sources files
    - **src/Includes**: All headers
    - **src/Includes/Dino.h**: 
    - **src/Dino.c**
- **Makefile**: make lib/ make test
- **README.md**: This file :D
- **test.c**: Test with C code
- **test.py**: Test with python code

## Example-of-1-output-frame

```sh
|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|
|                                                  |
|                                                  |
|                                                  |
|                           v                      |
| $                                                |
| $                                           %%   |
|##################################################|
|##################################################|
|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|
```
- **$** is the player
- **v** is a bird
- **%** is a bush
- **#** is the ground

For shift:
```sh
$
$       =>      $
```

## How-to-control-dino

- With C code:
    - **space**(' ') to jump
    - 'c' to shift
    - 'q' to stop

## To-go-further

We can improve the communication between the C library and python by using bytes or creating a **server**. For now, the backend is displaying the whole output, but it's better to just give the entity information.