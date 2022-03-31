bin/main: main.o MouseChangeableProgressbar.o Progressbar.o Resolution.o
	g++ main.o MouseChangeableProgressbar.o Progressbar.o Resolution.o -o bin/main -lsfml-graphics -lsfml-window -lsfml-system

main.o: src/main.cpp inc/stuff.hpp inc/Progressbar.hpp inc/MouseChangeableProgressbar.hpp inc/Resolution.hpp
	g++ -c src/main.cpp -lsfml-graphics -lsfml-window -I inc

Progressbar.o: src/Progressbar.cpp inc/Progressbar.hpp inc/stuff.hpp
	g++ -c src/Progressbar.cpp -lsfml-graphics -lsfml-window -I inc

MouseChangeableProgressbar.o: src/MouseChangeableProgressbar.cpp inc/MouseChangeableProgressbar.hpp inc/Progressbar.hpp
	g++ -c src/MouseChangeableProgressbar.cpp -lsfml-graphics -lsfml-window -I inc

Resolution.o: src/Resolution.cpp inc/Resolution.hpp
	g++ -c src/Resolution.cpp -lsfml-graphics -lsfml-window -I inc

clear:
	rm *.o bin/main

run:
	./bin/main
	