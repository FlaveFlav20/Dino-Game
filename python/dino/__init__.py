import ctypes
import typing

blackboxLib = ctypes.CDLL("/usr/lib/libdino.so")

# To create the setup structure (available in src/Includes/Dino.h)
class SetupDino(ctypes.Structure):
    _fields_ = [("server_out", ctypes.c_int),
                ("in_", ctypes.c_int),
                ("time_between_frame_ns", ctypes.c_ssize_t),
                ("chance", ctypes.c_ssize_t),
                ("min_chance", ctypes.c_ssize_t),
                ("dino_jump_height", ctypes.c_ssize_t),
                ("display_rows", ctypes.c_ssize_t),
                ("display_cols", ctypes.c_ssize_t),
                ("display_ground_height", ctypes.c_ssize_t)]

blackboxLib.start_dino.argtypes = [ctypes.POINTER(SetupDino)]
blackboxLib.start_dino.restype = ctypes.c_bool

class Dino:
    def __init__(self, fd_in: int, fd_out: int, 
                time_between_frames: int,
                chance: int, min_chance: int, 
                dino_jump_height: int,
                display_rows: int, display_cols: int, display_ground_height: int) -> None:


        self.setup = SetupDino(server_out=fd_out,
                                in_=fd_in,
                                time_between_frame_ns=time_between_frames,
                                chance=chance,
                                min_chance=min_chance,
                                dino_jump_height=dino_jump_height,
                                display_rows=display_rows,
                                display_cols=display_cols,
                                display_ground_height=display_ground_height)

    def start(self) -> bool:
        return blackboxLib.start_dino(ctypes.byref(self.setup))
