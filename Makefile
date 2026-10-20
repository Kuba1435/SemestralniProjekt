CC      = gcc
CFLAGS  = -std=c99 -Wall -Wextra -Iinclude
SRC     = $(wildcard src/*.c)
PROGRAM = festival

$(PROGRAM): $(SRC) include/*.h
	$(CC) $(CFLAGS) -o $(PROGRAM) $(SRC)

clean:
	rm -f $(PROGRAM) $(PROGRAM).exe
