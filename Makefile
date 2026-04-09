build: src
	g++ -g -o bin/battleship src/*.cpp

small: build
	./bin/battleship 5 5 docs/tiny.ships docs/tiny.ships