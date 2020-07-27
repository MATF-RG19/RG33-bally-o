PROGRAM = Bally-o
CC      = gcc
CFLAGS  = -g -Wall -std=c99 -I/usr/X11R6/include -I/usr/pkg/include
LDFLAGS = -L/usr/X11R6/lib -L/usr/pkg/lib
LDLIBS  = -lglut -lGLU -lGL -lm

$(PROGRAM) : main.o helper.o player.o settings.o collision.o map.o
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

.PHONY: clean
clean:
	rm -rf *o *~ $(PROGRAM)
