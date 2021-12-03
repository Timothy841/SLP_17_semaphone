all: main write

main: main.o
	gcc -c main.c main.o
	
main.o: main.c
	gcc -c main.c

write: write.o
	gcc -c write.c write.o

write.o: write.c
	gcc -c write.c

clean:
	rm *.o

run:
	./main
