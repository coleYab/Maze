all:
	gcc -o maze -Werror -Wall -Wextra -pedantic src/*.c -lSDL2 -lSDL2_image -lm

