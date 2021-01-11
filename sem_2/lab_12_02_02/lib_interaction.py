from ctypes import CDLL, POINTER, CFUNCTYPE
from ctypes import c_void_p, c_size_t, c_int, c_bool
from ctypes import sizeof, byref
from multiprocessing import Process, Value
from math import sqrt

condtition_f = CFUNCTYPE(c_bool, POINTER(c_int))


def setup_lib(lib_path: str) -> CDLL:
    lib = CDLL(lib_path)

    lib.lrotate.argtypes = [
        POINTER(c_int),
        c_size_t,
        c_size_t,
        c_size_t
    ]
    lib.lrotate.restype = c_int

    lib.cpybycond.argtypes = [
        POINTER(c_int),
        c_size_t,
        POINTER(c_int),
        c_size_t,
        c_size_t,
        condtition_f
    ]
    lib.cpybycond.restype = c_int
    return lib


def isfullsqr(a: POINTER(c_int)) -> c_bool:
    return sqrt(a.contents.value).is_integer()
