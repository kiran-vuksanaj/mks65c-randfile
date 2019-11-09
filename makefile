all: randfile.c
	gcc randfile.c
run:
	./a.out
clean:
	rm *.out
	rm randary
	rm *~
	rm *.o
