.PHONY: clean

CC=g++
OPTIONS= -g 
DEBUG= 

# He quitado tvectorcom.o y tlistacom.o porque no aparecen en tu carpeta todavía
_OBJ= tcomplejo.o 
OBJ = $(_OBJ)

# Regla para compilar cualquier archivo de prueba (tad01, tad02, etc.)
# Se usa poniendo: make tad01
tad%: tad%.cpp $(OBJ)
	$(CC) $(OPTIONS) $(DEBUG) -I. tad$*.cpp $(OBJ) -o tad$*

# Regla para crear los ficheros objeto (.o)
%.o: %.cpp %.h
	$(CC) $(OPTIONS) $(DEBUG) -c -I. -o $@ $<

clean:
	rm -f $(OBJ) tad01 tad02 tad03 tad04 tad05 tad06 tad07