from lib_interaction import CDLL, setup_lib
from interface import Tk, config


def main(lib: CDLL) -> None:
    root = Tk()
    config(root, lib)
    root.mainloop()

if __name__ == "__main__":
    lib = setup_lib("lib/libarr.so")
    main(lib)
