target: run

build:
	gcc main.c -o out -lSDL2

run: build
	./out

clean:
	rm out
