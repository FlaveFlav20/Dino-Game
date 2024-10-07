import sys
import os
import dino
  
import time
import io

import dino
import fcntl

import pygame
from pygame.locals import *

class Square(pygame.sprite.Sprite):
    def __init__(self):
        super(Square, self).__init__()
        self.surf = pygame.Surface((100, 100))
         
        # Define the color of the surface using RGB color coding.
        self.surf.fill((0, 200, 255))
        self.rect = self.surf.get_rect()

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
    screen = pygame.display.set_mode((500, 80))

    square1 = Square()
    square2 = Square()
    square3 = Square()
    square4 = Square()

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
                    print("Up")
                    file_in.write(" ")
                elif event.key == K_DOWN:
                    print("Down")
                    file_in.write("c")
            elif event.type == QUIT:
                input_data = io.StringIO("q")
                file_in.write("q")
                onGame = False
        
        file_in.flush()

        try:
            buffer = []
            for i in range(8):
                out = file_out.readline()
                buffer.append(out)
            for j in range(8):
                print(buffer[j], end='')
                for i in range(50):
                    if buffer[j][i] == "$":
                        screen.blit(square1.surf, (j * 100, i * 10))
                    elif buffer[j][i] == "v":
                        screen.blit(square2.surf, (j * 100, i * 10))
                    elif buffer[j][i] == "%":
                        screen.blit(square3.surf, (j * 100, i * 10))
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
    dino = dino.Dino(fd_in=r_game_in, fd_out=w_game_out, time_between_frames=5, chance=100, min_chance=10, dino_jump_height=4, display_rows=50, display_cols=8, display_ground_height=2)
    print("Close B")
    dino.start()
    os.close(w_game_out)
    os.close(w_game_in)
    print("Close Ha")
    exit(0)