#
# Makefil för att kompilera pacman med g++
#
# 
# Diagnosmeddelanden från kompilatorn (g++) filtreras av gccfilter
CCC = g++

# Kompilatorflaggor, lägg till '-g' om kompilering för avlusning ska göras 
CCFLAGS += -std=c++11 `sdl-config --cflags` `sdl-config --libs` -lSDL_image -lSDL_ttf

OBJECTS = Pacman.o

# Huvudmål - skapas med kommandot 'make' eller 'make pacman'.
pacman: $(OBJECTS)
	$(CCC) $(CCFLAGS) -o pacman $(OBJECTS)

# Delmål (flaggan -c avbryter innan länkning, objektkodsfil erhålls)
Pacman.o: src/Pacman.cpp 
	$(CCC) $(CCFLAGS) -c src/Pacman.cpp
# 'make clean' tar bort objektkodsfiler och 'core' (minnesdump).
clean:
	@ \rm -rf *.o *.gch pacman

# 'make zap' tar även bort det körbara programmet och reservkopior (filer
# som slutar med tecknet '~').
zap: clean
	@ \rm -rf pacman *~

# Se upp vid eventuell ändring, '*' får absolut inte finnas för sig!!!
#
# '@' medför att kommandot inte skrivs ut på skärmen då det utförs av make.
# 'rm' är ett alias för 'rm -i' på IDA:s system, '\rm' innebär att "original-
# versionen", utan flaggan '-i', används. 
