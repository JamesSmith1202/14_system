all: main.o
	gcc -o run main.o 

run: all
	./run

main.o: main.c
	gcc -c main.c

clean:
	rm -rf *~
	rm -rf *.o
	rm -rf run
