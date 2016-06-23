CXX=g++
XXFLAGS=-Wall -MMD
EXEC=quadris
OBJECTS=main.o window.o board.o block.o cell.o textdisplay.o
DEPENDS=${OBJECTS:.o=.d}
LIBS=-lX11

${EXEC}: ${OBJECTS}
	${CXX} ${XXFLAGS} ${OBJECTS} -o ${EXEC} ${LIBS}
-include ${DEPENDS}

clean:
	rm ${OBJECTS} ${EXEC}
