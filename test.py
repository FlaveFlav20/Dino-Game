import sys
import dino

dino = dino.Dino(file_in=sys.stdin, file_out=sys.stdout, time_between_frames=5 * 100000000, chance=100, min_chance=10, dino_jump_height=4, display_rows=25, display_cols=8, display_ground_height=2)
dino.start()