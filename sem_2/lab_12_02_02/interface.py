from tkinter import Tk, Canvas, Message, Label, Entry, Button, StringVar
from tkinter.messagebox import showinfo
from lib_interaction import *

lborder = 16
tborder = 16

entry_col = 130
button_col = 320

font = "roboto-mono 12"

arr_sym_tuple = ('BackSpace', 'space', 'minus')
step_sym_tuple = ('BackSpace')


def rotate_arr(lib: CDLL, arr: list, step: int, txt: StringVar) -> bool:
    if len(arr) == 0:
        return False

    c_arr = (c_int * len(arr))(*arr)

    rc = lib.lrotate(
        c_arr,
        c_size_t(len(c_arr)),
        c_size_t(sizeof(c_int)),
        c_size_t(step)
    )

    txt.set([i for i in c_arr])
    return True


def copyfullsrqs(lib: CDLL, arr: list[any], txt: StringVar) -> bool:
    if len(arr) == 0:
        return False

    arr_a = (c_int * len(arr))(*arr)
    arr_b = (c_int * len(arr))(*[-1] * len(arr))

    rc = lib.cpybycond(
        (arr_a),
        len(arr_a),
        (arr_b),
        len(arr_b),
        c_size_t(sizeof(c_int)),
        condtition_f(isfullsqr)
    )

    txt.set([i for i in arr_b if i >= 0])
    return True


def cmd_wrapper(cmd: callable, args: list[any]) -> None:
    try:
        if not cmd(*args):
            showinfo(message="Please, check you input data")
    except TypeError as identifier:
        print(identifier)


def press(event, syms: tuple[str]):
    if not (event.char.isdigit() or event.keysym in syms):
        return 'break'


def config(root: Tk, lib: CDLL):
    root.geometry("560x360")
    root.title("Shared lib interaction demo")
    root.resizable(False, False)

    Label(
        root,
        text="Array elems",
        font=font
    ).place(x=lborder, y=tborder)

    entry_array = Entry(root)
    entry_array.bind(
        '<KeyPress>',
        lambda event: press(event, arr_sym_tuple)
    )
    entry_array.place(height=22, x=entry_col, y=tborder)

    Label(
        root,
        text="Step",
        font=font
    ).place(x=lborder, y=48)

    entry_step = Entry(root)
    entry_step.bind(
        '<KeyPress>',
        lambda event: press(event, step_sym_tuple)
    )
    entry_step.place(height=22, x=entry_col, y=48)

    Label(
        root,
        text="Result",
        font=font
    ).place(x=lborder, y=80)

    txt = StringVar()

    Label(
        root,
        textvariable=txt,
        font=font
    ).place(x=lborder, y=100)

    Button(
        text="Rotate array",
        font=font,
        pady="4",
        command=lambda:
        cmd_wrapper(
            rotate_arr,
            [
                lib,
                list(map(int, entry_array.get().split())),
                0 if not list(map(int, entry_step.get().split()))
                else list(map(int, entry_step.get().split()))[0],
                txt
            ]
        )
    ).place(
        x=button_col,
        y=12
    )

    Button(
        text="Copy full sqr to 2nd arr",
        font=font,
        pady="4",
        command=lambda:
        cmd_wrapper(
            copyfullsrqs,
            [
                lib,
                list(map(int, entry_array.get().split())),
                txt
            ]
        )
    ).place(
        x=button_col,
        y=44
    )
