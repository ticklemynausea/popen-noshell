all:
	gcc -Wall popen-noshell.c -c
	gcc test.c popen-noshell.o -o test

clean:
	rm *.o
	rm test