TARGET = main

SRC = main.cpp event/fight.cpp lifeform/player.cpp

${TARGET} : ${SRC}
	g++ ${SRC} -o ${TARGET}




clean:
	rm -f $(TARGET)

