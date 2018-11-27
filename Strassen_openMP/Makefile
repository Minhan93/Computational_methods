CC=g++
CFLAGS=-I 
DEPS = matrix.h
OBJ = main.o matrix.o



%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
