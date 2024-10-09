import sys
import dino

dino = dino.Dino(fd_in=sys.stdin.fileno(), fd_out=sys.stdout.fileno(), time_between_frames=5, chance=30, min_chance=10, dino_jump_height=4, display_rows=50, display_cols=8, display_ground_height=2)
dino.start()
