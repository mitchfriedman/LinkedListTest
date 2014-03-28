# Flags that are sent to the compiler
# Do not change these
CFLAGS      =	-Wall -ansi -pedantic -g -Iinclude


music:
	gcc $(CFLAGS) src/music.c src/linkedList.c -o bin/music

test: 
	gcc $(CFLAGS) src/linkedList.c -o bin/listTest

clean:
	@ rm *.o
