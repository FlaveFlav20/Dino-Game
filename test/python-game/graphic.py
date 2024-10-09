# Our module
import dino

import fcntl
import io
import os
import sys
import time

from pygame_dino import Square, Player, Bird, Bush, Manage_enemy, display

import pygame
from pygame.locals import *

row: int = 50
col: int = 8
time_between_frame: int = 5
chance: int = 50
min_chance: int = 10
dino_jump_height: int = 4
display_ground_height: int = 2

# unblock: to set a non blocking file ) => a stream
def unblock(fd: int):
    flag = fcntl.fcntl(fd, fcntl.F_GETFL)
    fcntl.fcntl(fd, fcntl.F_SETFL, flag | os.O_NONBLOCK)

# One pipe for input, and one pipe for output
r_game_out, w_game_out = os.pipe()
r_game_in, w_game_in = os.pipe()

unblock(r_game_out)
unblock(w_game_out)
unblock(r_game_in)
unblock(w_game_in)

loop = True

# One process for input and one process to display output (because a write on stdout on python with C doesn't work idk why ;( )
pid = os.fork()

# The child will deal with pygame
if pid > 0:
    os.close(w_game_out)
    os.close(r_game_in)
    file_out = os.fdopen(r_game_out, "r")

    pygame.init()
    pygame.display.set_caption('Dino')
    screen = pygame.display.set_mode((row * 10, col * 10))

    player = Player()

    manage_enemy: Manage_enemy = Manage_enemy()

    onGame = True
    file_in = os.fdopen(w_game_in, "w")

    while onGame:
        # A sleep to wait the frame
        time.sleep(time_between_frame / 1000)

        # To get input
        for event in pygame.event.get():
            if event.type == KEYDOWN:
                if event.key == K_BACKSPACE:
                    onGame = False
                    file_in.write("q")
                if event.key == K_q:
                    onGame = False
                    file_in.write("q")
                elif event.key == K_UP:
                    file_in.write(" ")
                elif event.key == K_DOWN:
                    file_in.write("c")
            elif event.type == QUIT:
                input_data = io.StringIO("q")
                file_in.write("q")
                onGame = False
        
        # To force writing
        file_in.flush()

        try:
            # We'll get input as same as C output
            buffer = []
            max_itter = 10000
            i: int = 0
            begin: bool = False

            # This is a simple checking to know if we are at a begining of a sentence
            while i < col and i < max_itter:
                i+=1
                out = file_out.readline()
                if begin == False and out != "|" + "~" * row + "|\n":
                    continue
                elif begin == False and out == "|" + "~" * row + "|\n":
                    begin = True
                buffer.append(out)
            if i == max_itter:
                break
            display(buffer, row, col, screen, manage_enemy, player)
        except:
            continue

        # To display elements on screen
        pygame.display.flip()
    os.close(r_game_out)
    os.close(w_game_in)
    os.waitpid(pid, 0)
    exit(0)

# The parent will start the game
else:
    os.close(r_game_out)
    os.close(w_game_in)
    dino = dino.Dino(fd_in=r_game_in, fd_out=w_game_out, 
                    time_between_frames=time_between_frame, 
                    chance=chance, min_chance=min_chance, 
                    dino_jump_height=dino_jump_height, 
                    display_rows=row, display_cols=col, display_ground_height=display_ground_height)
    dino.start()
    os.close(w_game_out)
    os.close(w_game_in)
    exit(0)