CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -O3 -ffast-math

# macOS: Use brew's include and lib paths for GLFW
CFLAGS += -I/opt/homebrew/include
LDFLAGS = -L/opt/homebrew/lib -lglfw -framework OpenGL -lm

SRCS = main.c
OBJS = $(SRCS:.c=.o)
EXECUTABLE = game

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJS)
	$(CC) $(OBJS) -o $(EXECUTABLE) $(LDFLAGS) $(CFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ 

clean:
	rm -f $(OBJS) $(EXECUTABLE)

.PHONY: all clean