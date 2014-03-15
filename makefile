CC = g++
CFLAGS = -Wall
PROG = Game1

SRCS = 1.cpp
LIBS = -lglut -lGL -lGLU

all :$(PROG)
$(PROG): $(SRCS)
	$(CC) $(CFLAGS) -o $(PROG) $(SRCS) $(LIBS)

clean:
	rm -f $(PROG)
