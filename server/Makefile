##
#D Dino
#
# @file
# @version 0.1

SRCS = $(wildcard src/*.c)
OBJS = $(SRCS:.c=.o)

CFLAGS = -Wall -Werror -Wpedantic -std=c99 -g -D_POSIX_C_SOURCE=199309L

MAIN_SRC = main.c
MAIN_OBJ = main.o

TARGET = dinoServer

all: $(TARGET)
	$(CC) $(OBJS) $(MAIN_OBJ)  -o $(TARGET) $(CFLAGS)

$(TARGET): $(OBJS) $(MAIN_OBJ)

clean:
	rm $(OBJS) $(MAIN_OBJ) $(TARGET)

# end
