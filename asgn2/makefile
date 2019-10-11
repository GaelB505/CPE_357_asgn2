SHELL = /bin/sh
CC = gcc
CFLAGS = -Wall -O -ansi -c
LD = gcc
MAIN = fw
OBJS = $(MAIN).o
LDFLAGS = 
TEST = testFile


all: $(MAIN)

prog: $(MAIN)

clean:
	rm -f $(OBJS)


$(MAIN): $(MAIN).o
	$(LD) $(LDFLAGS) -o $(MAIN) $(MAIN).o 

$(MAIN).o: $(MAIN).c
	$(CC) $(CFLAGS) -o $(MAIN).o $(MAIN).c

test: $(MAIN)
	@echo "Testing $(MAIN):\n"
	./$(MAIN) $(TEST)
	@echo
	@echo Test Complete!
