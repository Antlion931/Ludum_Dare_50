FLAGS = -lsfml-graphics -lsfml-window -lsfml-system -I inc

RESOLUTION_HEADERS = inc/Resolution.hpp
TOOLKIT_HEADERS = inc/Toolkit.hpp
NODE_HEADERS = $(RESOLUTION_HEADERS) $(TOOLKIT_HEADERS) inc/Node.hpp

CONTAINER_HEADERS = $(NODE_HEADERS) inc/Container.hpp

PROGRESSBAR_HEADERS = $(NODE_HEADERS) $(RESOLUTION_HEADERS) inc/Progressbar.hpp
MOUSECHANGEABLEPROGRESSBAR_HEADERS = $(PROGRESSBAR_HEADERS) $(TOOLKIT_HEADERS) inc/MouseChangeableProgressbar.hpp

BUTTON_HEADERS = $(NODE_HEADERS) inc/Button.hpp
TEXTBUTTON_HEADERS = $(BUTTON_HEADERS) inc/TextButton.hpp

MAIN_HEADERS = $(MOUSECHANGEABLEPROGRESSBAR_HEADERS) $(TEXTBUTTON_HEADERS) $(CONTAINER_HEADERS) $(RESOLUTION_HEADERS) $(TOOLKIT_HEADERS)

bin/main: main.o Container.o Progressbar.o MouseChangeableProgressbar.o Resolution.o Button.o TextButton.o Node.o Toolkit.o
	g++ *.o -o bin/main $(FLAGS)

main.o: src/main.cpp $(MAIN_HEADERS)
	g++ -c src/main.cpp $(FLAGS)

Toolkit.o: src/Toolkit.cpp $(TOOLKIT_HEADERS)
	g++ -c src/Toolkit.cpp $(FLAGS)

Progressbar.o: src/Progressbar.cpp $(PROGRESSBAR_HEADERS)
	g++ -c src/Progressbar.cpp $(FLAGS)

MouseChangeableProgressbar.o: src/MouseChangeableProgressbar.cpp $(MOUSECHANGEABLEPROGRESSBAR_HEADERS)
	g++ -c src/MouseChangeableProgressbar.cpp $(FLAGS)

Resolution.o: src/Resolution.cpp $(RESOLUTION_HEADERS)
	g++ -c src/Resolution.cpp $(FLAGS)

Button.o: src/Button.cpp $(BUTTON_HEADERS)
	g++ -c src/Button.cpp $(FLAGS)

TextButton.o: src/TextButton.cpp $(TEXTBUTTON_HEADERS)
	g++ -c src/TextButton.cpp $(FLAGS)

Node.o: src/Node.cpp $(NODE_HEADERS)
	g++ -c src/Node.cpp $(FLAGS)

Container.o: src/Container.cpp $(CONTAINER_HEADERS)
	g++ -c src/Container.cpp $(FLAGS)

clear:
	rm *.o bin/main

run:
	./bin/main
