make: build run

build:
	g++ src/*.cpp -o bin/exe

run:
	./bin/exe