.PHONY : build run clean

SRC_DIR := ./src
INC_DIR := ./inc
OUT_DIR := ./out

CC := gcc
CFLAGS := -std=gnu99 -I$(INC_DIR) -Wall -Werror -Wfloat-equal -Wfloat-conversion -Wpedantic

SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(OUT_DIR)/%.o)
INCS := $(filter-out $(INC_DIR)/main.h, $(SRCS:$(SRC_DIR)/%.c=$(INC_DIR)/%.h))

EXEC := app.exe

build: $(EXEC)

run: $(EXEC)
	./$^

clean:
	@$(RM) $(EXEC) ${OUT_DIR}/*
	@rm -rf $(OUT_DIR)

$(EXEC): $(OBJS) $(INCS)
	@$(CC) $(CFLAGS) -o $@ $(OBJS)

$(OUT_DIR):
	@mkdir -p $(OUT_DIR)

${OUT_DIR}/%.o : ${SRC_DIR}/%.c $(OUT_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(INC_DIR)/%.h:
