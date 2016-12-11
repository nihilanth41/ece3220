IDIR =../include
CC=g++
CFLAGS=-I$(IDIR) -g -std=c++0x

ODIR=obj
LDIR =../lib

LIBS=-lm

_DEPS = Game.h Grid.h Shapes.h Util.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = Game.o Grid.o Shapes.o Util.o tetris.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.cpp $(DEPS)
		$(CC) -c -o $@ $< $(CFLAGS)

tetris: $(OBJ)
		$(CC) -o $@.bin $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
		rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 
