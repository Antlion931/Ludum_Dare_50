bin/main: main.o Progressbar.o MouseChangeableProgressbar.o Resolution.o Button.o TextButton.o Node.o Toolkit.o
	g++ *.o -o bin/main -lsfml-graphics -lsfml-window -lsfml-system

main.o: src/main.cpp inc/Progressbar.hpp inc/MouseChangeableProgressbar.hpp inc/Resolution.hpp inc/Node.hpp inc/Button.hpp inc/TextButton.hpp
	g++ -c src/main.cpp -lsfml-graphics -lsfml-window -I inc

Toolkit.o: src/Toolkit.cpp inc/Toolkit.hpp
	g++ -c src/Toolkit.cpp -lsfml-graphics -lsfml-window -I inc

Progressbar.o: src/Progressbar.cpp inc/Progressbar.hpp inc/Node.hpp
	g++ -c src/Progressbar.cpp -lsfml-graphics -lsfml-window -I inc

MouseChangeableProgressbar.o: src/MouseChangeableProgressbar.cpp inc/MouseChangeableProgressbar.hpp inc/Progressbar.hpp inc/Node.hpp 
	g++ -c src/MouseChangeableProgressbar.cpp -lsfml-graphics -lsfml-window -I inc

Resolution.o: src/Resolution.cpp inc/Resolution.hpp
	g++ -c src/Resolution.cpp -lsfml-graphics -lsfml-window -I inc

Button.o: src/Button.cpp inc/Button.hpp inc/Toolkit.hpp inc/Node.hpp
	g++ -c src/Button.cpp -lsfml-graphics -lsfml-window -I inc

TextButton.o: src/TextButton.cpp inc/Button.hpp inc/TextButton.hpp inc/Node.hpp
	g++ -c src/TextButton.cpp -lsfml-graphics -lsfml-window -I inc

Node.o: src/Node.cpp inc/Node.hpp
	g++ -c src/Node.cpp -lsfml-graphics -lsfml-window -I inc

clear:
	rm *.o bin/main

run:
	./bin/main
	