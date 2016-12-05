CC=gcc
CCFLAGS=-I /usr/include/cdk
LDFLAGS=-lcdk -lncurses
OBJ=fluomenu.o main.o about.o configdev.o
%.o: %.c
		$(CC) -c -o $@ $< $(CCFLAGS)

Fluorimeter: $(OBJ)
		$(CC) $^ $(LDFLAGS) -o $@

bb:	buttonbox_ex.o
		$(CC) $^ $(LDFLAGS) -o $@

clear:
		@echo "Remove all executables"		
		@rm -rf Fluorimeter
		@echo "Remove all object files"
		@rm -rf *.o

