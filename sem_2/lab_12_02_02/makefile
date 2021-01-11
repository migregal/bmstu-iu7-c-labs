.PHONY : all unit clean clean_all

RM := rm -rf
CC := gcc
LIBS_DIR := ./lib
LIB_INC_DIR := $(LIBS_DIR)/inc
LIB_NAME := arr

SRC_DIR := ./src
INC_DIR := ./inc
OUT_DIR := ./out

CFLAGS := -std=gnu99 				\
		-I$(INC_DIR) 				\
		-I$(LIB_INC_DIR) 			\
		-Wall -Werror 				\
		-Wfloat-equal 				\
		-Wfloat-conversion 			\
		-Wstrict-prototypes 		\
		-Wshadow 					\
		-Wconversion				\
		-Wpedantic

LFLAGS := -ldl -L$(LIBS_DIR) -Wl,-rpath=$(LIBS_DIR) -l$(LIB_NAME)

TESTS_DIR := ./unit_tests

LFLAGS := -I$(INC_DIR) -I$(LIB_INC_DIR) -lcheck -lpthread -lrt -lm -ldl -L$(LIBS_DIR) -Wl,-rpath=$(LIBS_DIR) -l$(LIB_NAME)
SRCS := $(wildcard $(TESTS_DIR)/*.c)
INCS := $(wildcard $(INC_DIR)/*.h)
OBJS := $(SRCS:$(UTESTS_DIR)/%.c=$(OUT_DIR)/%.o)

EXEC := check_app.exe

#--------------------------------------------------#

all:
	@(cd lib && make && cd ..)

unit: $(EXEC)
	@./$^ $(args)

clean:
	@$(RM) $(EXEC) $(OUT_DIR) __pycache__

clean_all: clean
	@(cd lib && make clean && cd ..)

#--------------------------------------------------#

$(EXEC): $(OBJS) $(INCS) all
	@$(CC) $(CFLAGS) -o $@ $(OBJS) $(LFLAGS)

$(OUT_DIR):
	@mkdir -p $(OUT_DIR)

$(INC_DIR)/%.h:

$(OUT_DIR)/%.o : $(SRC_DIR)/%.c $(OUT_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@ $(LFLAGS)

$(OUT_DIR)/check_%.o : $(UTESTS_DIR)/check_%.c $(OUT_DIR)
	@$(CC) $(CFLAGS) -o $@ -c $<
