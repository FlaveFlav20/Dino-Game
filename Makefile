##
#D Dino
#
# @file
# @version 0.1

SRCS = $(wildcard dinoBackend/src/*.c)
OBJS = $(SRCS:.c=.o)

OBJS += src/Dino.o

CFLAGS = -Wall -Werror -Wpedantic -std=c99 -g -D_POSIX_C_SOURCE=199309L -fPIC

MAIN_SRC = test.c
MAIN_OBJ = test.o

TARGET = dino

lib: CFLAGS += -fPIC
lib: lib$(TARGET).so

$(TARGET): $(OBJS) $(MAIN_OBJ) $(OBJS_s)

$(TARGET).so: $(OBJS) $(OBJS_s)
	$(CC) -shared $(OBJS) $(OBJS_s) -o $(TARGET).so $(CFLAGS)

lib$(TARGET).so: $(OBJS) $(OBJS_s)
	$(CC) -shared $(OBJS) $(OBJS_s) -o lib$(TARGET).so $(CFLAGS) && cp lib$(TARGET).so /usr/lib

debug: CFLAGS += -g
debug: $(TARGET)
	$(CC) $(OBJS) $(MAIN_OBJ) $(OBJS_s)  -o $(TARGET) $(CFLAGS)

test: $(OBJS) += $(MAIN_OBJ)
test: $(TARGET) $(OBJS_s)
	$(CC) $(OBJS) $(MAIN_OBJ) $(OBJS_s)  -o $(TARGET) $(CFLAGS)

clean:
	rm -f $(OBJS) $(MAIN_OBJ) $(TARGET) $(TARGET).so

# end
