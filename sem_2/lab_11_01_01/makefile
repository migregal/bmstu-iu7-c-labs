.PHONY : all run debug runmem gcov clean func check unit

SRC_DIR := ./src
INC_DIR := ./inc
OUT_DIR := ./out
UTESTS_DIR := ./unit_tests
FTESTS_DIR := ./func_tests

CC := gcc
CFLAGS := -std=gnu99 -w -I$(INC_DIR) -g3

SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(OUT_DIR)/%.o)
INCS := $(filter-out $(INC_DIR)/main.h, $(SRCS:$(SRC_DIR)/%.c=$(INC_DIR)/%.h))

U_CFLAGS := -lcheck -lpthread -lrt
U_SRCS := $(wildcard $(UTESTS_DIR)/*.c)
U_OBJS := $(U_SRCS:$(UTESTS_DIR)/%.c=$(OUT_DIR)/%.o)
U_OBJS += $(filter-out $(OUT_DIR)/main.o, $(OBJS))

EXEC := app.exe
UEXEC := unit_tests.exe

all: $(EXEC)

run: $(EXEC)
	./$^ $(args)

$(EXEC): $(OBJS) $(INCS)
	@$(CC) $(CFLAGS) -o $@ $(OBJS)

debug : CFLAGS += -g -fno-inline -fno-omit-frame-pointer -O0 --coverage
debug : all

runmem : debug
	drmemory -- ./$(EXEC) $(args)

gcov :
	@$(RM) $(OUT_DIR)/*.c.gcov
	@gcov -d $(OUT_DIR)/*.gcda
	@mv *.c.gcov $(OUT_DIR)

func: $(EXEC)
	@bash $(FTESTS_DIR)/run_tests.sh ./$(EXEC)

unit : $(UEXEC)
	@./$(UEXEC)

$(UEXEC) : $(U_OBJS) $(INCS)
	@$(CC) $(CFLAGS) -o $@ $(U_OBJS) $(U_CFLAGS)

cppcheck: $(SRCS)
	@cppcheck -I$(INC_DIR) -q --std=c99 --platform=unix64 \
--enable=all --template='{id} {file}:{line} {message}' $^

$(OUT_DIR):
	@mkdir -p $(OUT_DIR)

${OUT_DIR}/%.o : ${SRC_DIR}/%.c $(OUT_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OUT_DIR)/check_%.o : $(UTESTS_DIR)/check_%.c $(OUT_DIR)
	@$(CC) $(CFLAGS) -o $@ -c $<

$(INC_DIR)/%.h:

clean:
	@$(RM) $(EXEC) $(UEXEC) ${OUT_DIR}/*
	@rm -rf $(OUT_DIR)
