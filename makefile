TARGET = main

SRC = main.cpp  gameloop.cpp event/fight.cpp lifeform/player.cpp assets/dialog/intro.cpp

${TARGET} : ${SRC}
	g++ ${SRC} -o ${TARGET}


go:
	./main


clean:
	rm -f $(TARGET)

#make pour compiler le projet
#make go pour lancer le projet compiler
#make clean pour supprimer le projet