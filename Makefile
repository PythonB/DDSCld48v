all:
	cd src && g++ ddsc.cpp player.cpp monster.cpp -o ddsc -lsfml-graphics -lsfml-window -lsfml-system -w
	cp src/ddsc .
