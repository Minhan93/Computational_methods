CC=g++
#SCFLAGS=-I 
DEPS = sort.h List_merge.h List_quick.h
OBJ = main.o sort.o List_merge.o List_quick.o 


%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: $(OBJ)
	$(CC) -o $@ $^ 