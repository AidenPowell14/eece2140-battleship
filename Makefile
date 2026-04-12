build: src
	g++ -g -o battleship-game src/*.cpp

small: build
	./battleship-game 5 5 docs/tiny.ships docs/tiny.ships

std: build
	./battleship-game 10 10 docs/standard.ships docs/standard.ships

clean: 
	rm -f battleship-game