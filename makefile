
LIBS=-lsfml-graphics -lsfml-window -lsfml-system
CXXFLAGS= -g -Iinc -Wall -pedantic -std=c++11

__start__:a.out
	./a.out 



a.out: obj obj/main.o  obj/Plansza.o obj/Gra.o
           
	g++ -g -Wall -pedantic -std=c++11   obj/main.o obj/Plansza.o obj/Gra.o -lsfml-graphics -lsfml-window -lsfml-system
                      
obj/main.o: src/main.cpp inc/Plansza.hh inc/Gra.hh
	g++ -c ${CXXFLAGS} -o  obj/main.o src/main.cpp -lsfml-graphics -lsfml-window -lsfml-system

obj/Plansza.o: src/Plansza.cpp inc/Plansza.hh
	g++ -c ${CXXFLAGS} -o  obj/Plansza.o src/Plansza.cpp -lsfml-graphics -lsfml-window -lsfml-system

obj/Gra.o: src/Gra.cpp inc/Gra.hh
	g++ -c ${CXXFLAGS} -o  obj/Gra.o src/Gra.cpp  -lsfml-graphics -lsfml-window -lsfml-system