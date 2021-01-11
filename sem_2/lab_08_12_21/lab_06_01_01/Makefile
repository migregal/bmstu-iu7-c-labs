CC = gcc
CFLAGS = -std=c99 -Wall -Werror -Wextra -pedantic -Wconversion -Wfloat-equal -Wredundant-decls -Wsign-conversion -Wvla

FUNC_C = ./*.c
FUNC_O = ./*.o

OBJ = $(patsubst %.c, %.o, $(wildcard $(FUNC_C)))
OBJ_MAIN = $(patsubst %.c, %.o, $(wildcard *.c))

CPPCHECK_FLAGS = -q --std=c99 --platform=unix64 --enable=all --template='{id} {file}:{line} {message}'

main: $(OBJ) $(OBJ_MAIN)
	$(CC) -o $@ $^
	cppcheck $(CPPCHECK_FLAGS) ./

test:
	bash ./func_tests/run_tests.sh

run:
	./app.exe

cppcheck:
	cppcheck $(CPPCHECK_FLAGS) ./

clean:
	rm $(FUNC_O) main
