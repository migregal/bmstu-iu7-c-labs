.PHONY : all clean

RM := rm -rf
CC := gcc

SRC_DIR := src
INC_DIR := inc
OUT_DIR := out

CFLAGS := -std=gnu99 	\
		-I$(INC_DIR) 	\
		-Wall -Werror 		\
		-Wfloat-equal 		\
		-Wfloat-conversion 	\
		-Wstrict-prototypes \
		-Wshadow 			\
		-Wconversion		\
		-Wpedantic

LFLAGS := -lpthread

INCS := $(wildcard $(SRC_DIR)/*.h)
SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(OUT_DIR)/%.o)

NAME := arr

all: $(NAME)

clean:
	@$(RM) *.so *.a $(OUT_DIR)

#--------------------------------------------------#

$(OUT_DIR):
	@mkdir -p $(OUT_DIR)

$(OUT_DIR)/%.o : $(SRC_DIR)/%.c $(OUT_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@ $(LFLAGS)

$(INC_DIR)/%.h:

$(NAME): CFLAGS += -fPIC
$(NAME): $(OBJS) $(SRCS) $(INCS) $(OUT_DIR)
	@$(CC) -shared -o lib$(NAME).so $(OBJS) $(LFLAGS)
