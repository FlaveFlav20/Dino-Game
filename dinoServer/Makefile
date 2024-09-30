##
#D Dino
#
# @file
# @version 0.1

SRCS = $(wildcard src/*.c)
OBJS = $(SRCS:.c=.o)

CFLAGS = -Wall -Werror -Wpedantic -std=c99 -g -D_POSIX_C_SOURCE=199309L -fPIC

MAIN_SRC = test.c
MAIN_OBJ = test.o

TARGET = dinoServer

lib: CFLAGS += -fPIC
lib: $(TARGET).so

$(TARGET): $(OBJS) $(MAIN_OBJ)

$(TARGET).so: $(OBJS)
	$(CC) -shared $(OBJS) -o $(TARGET).so $(CFLAGS)

debug: CFLAGS += -g
debug: $(TARGET)

test: $(OBJS) += $(MAIN_OBJ)
test: $(TARGET)
	$(CC) $(OBJS) $(MAIN_OBJ)  -o $(TARGET) $(CFLAGS)

clean:
	rm $(OBJS) $(MAIN_OBJ) $(TARGET) $(TARGET).so

# end
