CC=gcc
CCFLAGS=-Ofast -I /usr/include/cdk
LDFLAGS=-Ofast -lcdk -lncurses	
OBJ=fluomenu.o main.o about.o configdev.o \
	configltr11module.o \
	configltr210module.o


%.o: %.c
		$(CC) -c -o $@ $< $(CCFLAGS)

Fluorimeter: $(OBJ)
		$(CC) $^ $(LDFLAGS) -o $@

all: clear Fluorimeter


clear:
		@echo "Remove all executables"		
		@rm -rf Fluorimeter
		@echo "Remove all object files"
		@rm -rf *.o

