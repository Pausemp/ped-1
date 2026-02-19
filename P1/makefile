<<<<<<< HEAD
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
=======
.PHONY= doc clean

CC=g++-13
OPTIONS= -g 
DEBUG= #-D DEBUG
LIBDIR=lib
INCLUDEDIR=include
_OBJ= tcomplejo.o
OBJ = $(patsubst %,$(LIBDIR)/%,$(_OBJ))

tad:    src/tad.cpp $(OBJ)
	$(CC) $(OPTIONS) $(DEBUG) -I$(INCLUDEDIR) src/tad.cpp $(OBJ) -o tad

$(LIBDIR)/%.o : $(LIBDIR)/%.cpp $(INCLUDEDIR)/%.h
	$(CC) $(OPTIONS) $(DEBUG) -c -I$(INCLUDEDIR) -o $@ $<


clean:
	rm -f $(OBJ) 
>>>>>>> 55dde8f9783d82de3cfa8d4d6c5b8b9a47f3b878
