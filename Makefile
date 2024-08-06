all:
	gcc hyperdrive.c -o run -lraylib -lm -Wall
clean:
	rm run
	clear
