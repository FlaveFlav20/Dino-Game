##
# Dino-Game
#
# @file
# @version 0.1

CC := gcc
CFLAGS := -Wall -Werror -Wpedantic -std=c99
LDFLAGS :=

SRCS := $(wildcard src/*.c)
OBJS := $(SRCS:.c=.o)

MAIN_SRC := main.c
MAIN_OBJ := $(MAIN_SRC:.c=.o)

TARGET := dinoClient

all: $(TARGET)

$(TARGET): $(OBJS) $(MAIN_OBJ)
	$(CC) $(OBJS) $(MAIN_OBJ) -o $(TARGET) $(LDFLAGS) $(CFLAGS)

lib: CFLAGS += -fPIC
lib: $(TARGET).so

$(TARGET).so: $(OBJS) $(MAIN_OBJ)
	$(CC) -shared $(OBJS) $(MAIN_OBJ) -o $(TARGET).so $(CFLAGS)

debug: CFLAGS += -g
debug: $(TARGET)

clean:
	rm $(OBJS) $(MAIN_OBJ) $(TARGET) $(TARGET).so

# end
