CC = gcc
CFLAGS = -Wall -Wextra -std=c11 `sdl2-config --cflags`
LDFLAGS = `sdl2-config --libs` -lSDL2_image -lSDL2_ttf -lSDL2_mixer # Add other SDL2 libraries as needed (e.g., image, ttf, mixer)

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