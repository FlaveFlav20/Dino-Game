import sys
import os
import dino
  
import time
import io

import dino
import fcntl

from pygame_dino import Square, Player, Bird, Bush, Manage_enemy, display

import pygame
from pygame.locals import *

row: int = 50
col: int = 8

def unblock(fd: int):
    flag = fcntl.fcntl(fd, fcntl.F_GETFL)
    fcntl.fcntl(fd, fcntl.F_SETFL, flag | os.O_NONBLOCK)

r_game_out, w_game_out = os.pipe()
r_game_in, w_game_in = os.pipe()

unblock(r_game_out)
unblock(w_game_out)
unblock(r_game_in)
unblock(w_game_in)

loop = True
pid = os.fork()

if pid > 0:
    os.close(w_game_out)
    os.close(r_game_in)
    file_out = os.fdopen(r_game_out, "r")

    pygame.init()
    screen = pygame.display.set_mode((row * 10, col * 10))

    player = Player()

    manage_enemy: Manage_enemy = Manage_enemy()

    onGame = True
    file_in = os.fdopen(w_game_in, "w")

    while onGame:
        time.sleep(0.005)
        for event in pygame.event.get():
            if event.type == KEYDOWN:
                if event.key == K_BACKSPACE:
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
        
        file_in.flush()

        screen.fill((0, 0, 0))
        manage_enemy.clear()

        try:
            buffer = []
            for i in range(col):
                out = file_out.readline()
                buffer.append(out)
            display(buffer, row, col, screen, manage_enemy, player)
            sys.stdout.flush()
        except:
            continue
        pygame.display.flip()
        if onGame == False:
            print("On game: ", onGame)
    print("Close")
    os.close(r_game_out)
    os.close(w_game_in)
    os.waitpid(pid, 0)
    exit(0)

else:
    os.close(r_game_out)
    os.close(w_game_in)
    dino = dino.Dino(fd_in=r_game_in, fd_out=w_game_out, time_between_frames=5, chance=50, min_chance=10, dino_jump_height=4, display_rows=row, display_cols=col, display_ground_height=2)
    print("Close B")
    dino.start()
    os.close(w_game_out)
    os.close(w_game_in)
    print("Close Ha")
    exit(0)