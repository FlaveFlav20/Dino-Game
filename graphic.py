from tkinter import *
import sys
import os
import dino

import subprocess
import os 
  
import time

import sys
import dino
import fcntl

def unblock(fd: int):
    flag = fcntl.fcntl(fd, fcntl.F_GETFL)
    fcntl.fcntl(fd, fcntl.F_SETFL, flag | os.O_NONBLOCK)

r_game_out, w_game_out = os.pipe()
#r_game_in, w_game_in = os.pipe()

unblock(r_game_out)
unblock(w_game_out)

loop = True
pid = os.fork()

if pid > 0:
    os.close(w_game_out)
    file_out = os.fdopen(r_game_out, "r")
    while loop:
        try:
            sleep(0.005)
            out = file_out.readline()
            print(out, end="")
        except: 
            print("Xhat")
            continue
    os.close(r_game_out)
    exit(0)
        
else:
    os.close(r_game_out)
    dino = dino.Dino(fd_in=sys.stdin.fileno(), fd_out=w_game_out, time_between_frames=5, chance=100, min_chance=10, dino_jump_height=4, display_rows=50, display_cols=8, display_ground_height=2)
    dino.start()
    os.close(w_game_out)
    exit(0)
