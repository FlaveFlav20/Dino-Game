##
#D Dino
#
# @file
# @version 0.1

SRCS = $(wildcard src/*.c)
OBJS = $(SRCS:.c=.o)

CFLAGS = -Wall -Werror -Wpedantic -std=c99 -g -D_POSIX_C_SOURCE=199309L -fPIC

MAIN_SRC = main.c
MAIN_OBJ = main.o

TARGET = dinoServer

all: $(TARGET)
	$(CC) $(OBJS) $(MAIN_OBJ)  -o $(TARGET) $(CFLAGS)

$(TARGET): $(OBJS) $(MAIN_OBJ)

lib: CFLAGS += -fPIC
lib: $(TARGET).so

$(TARGET).so: $(OBJS) $(MAIN_OBJ)
	$(CC) -shared $(OBJS) $(MAIN_OBJ) -o $(TARGET).so $(CFLAGS)

debug: CFLAGS += -g
debug: $(TARGET)

clean:
	rm $(OBJS) $(MAIN_OBJ) $(TARGET) $(TARGET).so

# end
