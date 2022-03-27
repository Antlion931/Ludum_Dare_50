bin/main: main.o
	g++ main.o -o bin/main

main.o: src/main.cpp
	g++ -c main.cpp

clear:
	rm *.o bin/main