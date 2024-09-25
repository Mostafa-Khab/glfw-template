run: main
	./build/main

main: main.c src/*.c src/*.h
	gcc main.c /usr/local/src/glad/glad.c src/*.c -o build/main -lglfw -lX11 -lm
