# fichero Makefile
#
BIN=./bin/
SRC=./src/
INC=./include/
OBJ=./obj/
# nombre del fichero ejecutable
#
TARGETS= practica4

# banderas para el compilador (C y C++). Se indican los directorios donde se puenden
# encontrar ficheros para incluir mediante la opcion -I
#
CFLAGS=    -I$(INC)
CXXFLAGS=  -I$(INC)


# orden que sera ejecutada por defecto
#
default :
	g++ -g -std=c++11 -o $(BIN)$(TARGETS) $(SRC)principal.cpp $(CXXFLAGS)
#
#

clean:
	rm -f $(OBJ)*.o
	rm -f $(BIN)$(TARGETS)

#
#
redo:
	touch *.cpp
	make

#
#
tgz:
	rm -f $(OBJ)*.o
	rm -f $(BIN)$(TARGETS)
	tar -zcvf $(TARGETS).tgz *
