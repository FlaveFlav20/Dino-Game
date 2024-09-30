import ctypes
import typing

blackboxLib = ctypes.CDLL("/usr/lib/libdino.so.so")

class SetupDino(ctypes.Structure):
    _fields_ = [("server_in", ctypes.c_void_p),
                ("server_out", ctypes.c_void_p),
                ("in_", ctypes.c_void_p),
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
    def __init__(self, file_in: typing.IO, file_out: typing.IO, time_between_frames: int,
                chance: int, min_chance: int, dino_jump_height: int,
                display_rows: int, display_cols: int, display_ground_height: int):
        libc = ctypes.CDLL('libc.so.6')
        fd_in = file_in.fileno()
        fd_out = file_out.fileno()
        FILE_p = libc.fdopen
        FILE_p.restype = ctypes.c_void_p
        FILE_p.argtypes = [ctypes.c_int, ctypes.c_char_p]

        self.setup = SetupDino(server_in=FILE_p(fd_in, b"r+"),
                                server_out=FILE_p(fd_out, b"w+"),
                                in_=FILE_p(fd_in, b"r+"),
                                time_between_frame_ns=time_between_frames,
                                chance=chance,
                                min_chance=min_chance,
                                dino_jump_height=dino_jump_height,
                                display_rows=display_rows,
                                display_cols=display_cols,
                                display_ground_height=display_ground_height)

    def start(self) -> bool:
        return blackboxLib.start_dino(ctypes.byref(self.setup))
