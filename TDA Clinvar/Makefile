# fichero Makefile
#
BIN=./bin/
SRC=./src/
INC=./include/
OBJ=./obj/
# nombre del fichero ejecutable
#
TARGETS= clinvar

# banderas para el compilador (C y C++). Se indican los directorios donde se puenden
# encontrar ficheros para incluir mediante la opcion -I
#
CFLAGS=    -g -I/usr/include -I$(INC).
CXXFLAGS=  -g -I/usr/include -I$(INC).

# definicion del compilador
#
CC = g++ -std=c++11

SOURCES  := $(wildcard $(SRC)*.cpp)
INCLUDES := $(wildcard $(INC)*.h)
OBJECTS  := $(SOURCES:$(SRC)%.c=$(OBJ)%.o)


# orden que sera ejecutada por defecto
#
default :$(BIN)$(TARGETS)

# regla de ejecucion
#
$(BIN)$(TARGETS) : $(OBJECTS)
	$(CC) -o $@ $(CXXFLAGS) $(OBJECTS)
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
