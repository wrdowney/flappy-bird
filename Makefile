CC = gcc
CFLAGS = -Wall -Wextra -std=c11
# Adjust include paths if GLFW headers are not in the default location
# CFLAGS += -I/usr/local/include 
LDFLAGS = -lglfw -lGL -lm -ldl -lpthread # Common libraries needed for GLFW on Linux
# Adjust lib paths if GLFW library is not in the default location
# LDFLAGS += -L/usr/local/lib

SRCS = main.c
OBJS = $(SRCS:.c=.o)
EXECUTABLE = game

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJS)
	$(CC) $(OBJS) -o $(EXECUTABLE) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXECUTABLE)

.PHONY: all clean