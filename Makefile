CC = gcc
CFLAGS = -Wall -Wextra -std=c11
CFLAGS += -I/opt/homebrew/include
LDFLAGS = -L/opt/homebrew/lib -lglfw -framework OpenGL -lm

SRCS = main.c ball.c
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