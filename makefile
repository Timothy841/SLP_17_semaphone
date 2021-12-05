all: main write
	gcc -o main main.o
	gcc -o write write.o

main: main.c
	gcc -c main.c

write: write.c
	gcc -c write.c

clean:
	rm *.o

run:
	./main
