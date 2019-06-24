IDIR =include
CC=clang++
CFLAGS=-I$(IDIR) -std=c++17 -O2

ODIR=src/obj
SDIR=src
LDIR =../lib

LIBS=-lSDL2 -lSDL2_ttf -lSDL2_image -lSDL2_mixer -lstdc++fs -lm -lpthread

_DEPS = Core.hpp Filesys.hpp Media.hpp Render.hpp Game.hpp Entity.hpp Vec2.hpp Cmd.hpp Log.hpp Font.hpp Commands.hpp Events.hpp Music.hpp
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o Core.o Core_Console.o Media.o Filesys.o Render.o Game.o Entity.o Vec2.o Cmd.o Log.o Font.o Commands.o Events.o Music.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

OUTPUT = quakem

$(ODIR)/%.o: $(SDIR)/%.cpp $(DEPS)
	$(CC) $(CFLAGS) -MD -MP -c -o $@ $<
make: $(OBJ)
	$(CC) -o $(OUTPUT) $^ $(CFLAGS) $(LIBS)
		
debug: $(OBJ)
	$(CC) -g -o $(OUTPUT) $^ $(CFLAGS) $(LIBS) 

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~

-include $(OBJ:.o=.d)
