bin/main: main.o
	g++ main.o -o bin/main -lsfml-graphics -lsfml-window -lsfml-system
main.o: src/main.cpp inc/stuff.hpp
	g++ -c src/main.cpp -lsfml-graphics -lsfml-window -I inc

clear:
	rm *.o bin/main

run:
	./bin/main