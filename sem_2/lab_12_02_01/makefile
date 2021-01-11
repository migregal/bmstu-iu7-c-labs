.PHONY : all libs debug gcov func unit clean

RM := rm -rf
CC := gcc
AR := ar

#--------------------------------------------------#

LIBS_DIR := ./lib
LIB_SRC_DIR := $(LIBS_DIR)/src
LIB_INC_DIR := $(LIBS_DIR)/inc
LIB_OUT_DIR := $(LIBS_DIR)/out

LIB_INCS := $(wildcard $(LIB_SRC_DIR)/*.h)

LIB_CFLAGS := -std=gnu99 	\
		-I$(LIB_INC_DIR) 	\
		-Wall -Werror 		\
		-Wfloat-equal 		\
		-Wfloat-conversion 	\
		-Wstrict-prototypes \
		-Wshadow 			\
		-Wconversion		\
		-Wpedantic

LIB_LFLAGS := -lpthread

#--------------------------------------------------#

LIB_SRCS := $(wildcard $(LIB_SRC_DIR)/*.c)
LIB_OBJS := $(LIB_SRCS:$(LIB_SRC_DIR)/%.c=$(LIB_OUT_DIR)/%.o)

SO_NAME := soutils
A_NAME := autils

#--------------------------------------------------#

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

LFLAGS := -L$(LIBS_DIR) -Wl,-rpath=$(LIBS_DIR)

INCS := $(wildcard $(SRC_DIR)/*.h)
SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(OUT_DIR)/main.o
OBJS_DL := $(OUT_DIR)/main_dl.o

FTESTS_DIR := ./func_tests

#--------------------------------------------------#

UTESTS_DIR := ./unit_tests

U_LFLAGS := -I$(INC_DIR) -I$(LIB_INC_DIR) -lcheck -lpthread -lrt -lm -L$(LIBS_DIR) -Wl,-rpath=$(LIBS_DIR) -l$(A_NAME)
U_SRCS := $(wildcard $(UTESTS_DIR)/*.c)
U_OBJS := $(U_SRCS:$(UTESTS_DIR)/%.c=$(OUT_DIR)/%.o)
U_OBJS += $(filter-out $(OUT_DIR)/main.o, $(OBJS))

#--------------------------------------------------#

EXEC := app.exe
EXEC_SO := app_so.exe
EXEC_DL := app_dl.exe

UEXEC := check_app.exe

all: $(EXEC) $(EXEC_SO) $(EXEC_DL)

cppcheck: $(SRCS)
	@cppcheck -I$(INC_DIR) -I$(LIB_INC_DIR) -q --std=c99 --platform=unix64 	\
	--enable=all --suppress=missingIncludeSystem 			\
	--template='(id) (file):(line) (message)' $^

libs: shared_libs static_libs

shared_libs: $(SO_NAME)
static_libs: $(A_NAME)

debug : CFLAGS += -g -fno-inline -fno-omit-frame-pointer -O0 --coverage
debug : LFLAGS += -lgcov
debug : LIB_CFLAGS += -g -fno-inline -fno-omit-frame-pointer -O0 --coverage
debug : LIB_LFLAGS += -lgcov
debug : $(EXEC)

gcov :
	@$(RM) $(OUT_DIR)/*.c.gcov
	@gcov -d $(OUT_DIR)/*.gcda
	@gcov -d $(LIB_OUT_DIR)/*.gcda
	@mv *.c.gcov $(OUT_DIR)

func: $(EXEC) $(EXEC_SO) $(EXEC_DL)
	@bash $(FTESTS_DIR)/run_tests.sh ./$(EXEC)
	@bash $(FTESTS_DIR)/run_tests.sh ./$(EXEC_SO)
	@bash $(FTESTS_DIR)/run_tests.sh ./$(EXEC_DL)

unit: $(UEXEC)
	@./$^ $(args)

clean:
	@$(RM) 				\
	$(EXEC) 			\
	$(EXEC_SO) 			\
	$(EXEC_DL) 			\
	$(UEXEC) 			\
	$(LIBS_DIR)/*.so 	\
	$(LIBS_DIR)/*.a 	\
	$(LIB_OUT_DIR) 		\
	$(OUT_DIR)

#--------------------------------------------------#

$(EXEC): LFLAGS += -l$(A_NAME)
$(EXEC): $(OBJS) $(INCS) libs
	@$(CC) $(CFLAGS) -o $@ $(OBJS) $(LFLAGS)

$(EXEC_SO): LFLAGS += -l$(SO_NAME)
$(EXEC_SO): $(OBJS) $(INCS) libs
	@$(CC) $(CFLAGS) -o $@ $(OBJS) $(LFLAGS)

$(EXEC_DL): LFLAGS += -ldl
$(EXEC_DL): $(OBJS_DL) $(INCS) libs
	@$(CC) $(CFLAGS) -o $@ $(OBJS_DL) $(LFLAGS)

$(UEXEC): $(U_OBJS) $(INCS) libs
	@$(CC) $(CFLAGS) -o $@ $(U_OBJS) $(U_LFLAGS)

$(OUT_DIR):
	@mkdir -p $(OUT_DIR)

$(INC_DIR)/%.h:

$(OUT_DIR)/%.o : $(SRC_DIR)/%.c $(OUT_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@ $(LFLAGS)

$(OUT_DIR)/check_%.o : $(UTESTS_DIR)/check_%.c $(OUT_DIR)
	@$(CC) $(CFLAGS) -o $@ -c $<

#--------------------------------------------------#

$(LIB_OUT_DIR):
	@mkdir -p $(LIB_OUT_DIR)

$(LIB_OUT_DIR)/%.o : $(LIB_SRC_DIR)/%.c $(LIB_OUT_DIR)
	@$(CC) $(LIB_CFLAGS) -c $< -o $@ $(LIB_LFLAGS)

$(LIB_INC_DIR)/%.h:

$(A_NAME): $(LIB_OBJS) $(LIB_SRCS) $(LIB_INCS) $(LIB_OUT_DIR)
	@$(AR) -rc $(LIBS_DIR)/lib$(A_NAME).a $(LIB_OBJS)
	@ranlib $(LIBS_DIR)/lib$(A_NAME).a

$(SO_NAME): LIB_CFLAGS += -fPIC
$(SO_NAME): $(LIB_OBJS) $(LIB_SRCS) $(LIB_INCS) $(LIB_OUT_DIR)
	@$(CC) -shared -o 				\
	$(LIBS_DIR)/lib$(SO_NAME).so 	\
	$(LIB_OBJS) $(LIB_LFLAGS)
