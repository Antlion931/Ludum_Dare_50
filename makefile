bin/main: main.o Node.o Button.o TextButton.o
	g++ main.o Node.o Button.o TextButton.o -o bin/main -lsfml-graphics -lsfml-window -lsfml-system

main.o: src/main.cpp inc/Button.hpp inc/Node.hpp inc/TextButton.hpp inc/Toolkit.hpp
	g++ -c src/main.cpp -lsfml-graphics -lsfml-window -I inc

Button.o: src/Button.cpp inc/Button.hpp inc/Toolkit.hpp
	g++ -c src/Button.cpp -lsfml-graphics -lsfml-window -I inc

TextButton.o: src/TextButton.cpp inc/Button.hpp inc/TextButton.hpp
	g++ -c src/TextButton.cpp -lsfml-graphics -lsfml-window -I inc

Node.o: src/Node.cpp inc/Node.hpp inc/Toolkit.hpp
	g++ -c src/Node.cpp -lsfml-graphics -lsfml-window -I inc

clear:
	rm *.o bin/main

run:
	./bin/main