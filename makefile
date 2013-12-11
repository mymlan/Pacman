#
# Makefil för att kompilera pacman med g++
#
# 

# Diagnosmeddelanden från kompilatorn (g++) filtreras av gccfilter
CCC = gccfilter -c -a g++

# Kompilatorflaggor, lägg till '-g' om kompilering för avlusning ska göras 
CCFLAGS += -std=c++11 `sdl-config --cflags` `sdl-config --libs` -lSDL_image -lSDL_ttf

# Preprocessorflaggor, -I lägger till en filkatalog i inkluderingssökvägen.
CPPFLAGS += -I$(src)


# Objektkodsmoduler som ingår i det kompletta spelet.
OBJECTS = Pacman.o

# Huvudmål - skapas med kommandot 'make' eller 'make pacman'.
Pacman: $(OBJECTS) makefile
	$(CCC) $(CPPFLAGS) $(CCFLAGS) $(LDFLAGS) -o test $(OBJECTS)

# Delmål (flaggan -c avbryter innan länkning, objektkodsfil erhålls)
Pacman.o: src/Pacman.cpp
	$(CCC) $(CPPFLAGS) $(CCFLAGS) -c src/Pacman.cpp


# 'make clean' tar bort objektkodsfiler och 'core' (minnesdump).
clean:
	@ \rm -rf *.o *.gch core

# 'make zap' tar även bort det körbara programmet och reservkopior (filer
# som slutar med tecknet '~').
zap: clean
	@ \rm -rf test *~

# Se upp vid eventuell ändring, '*' får absolut inte finnas för sig!!!
#
# '@' medför att kommandot inte skrivs ut på skärmen då det utförs av make.
# 'rm' är ett alias för 'rm -i' på IDA:s system, '\rm' innebär att "original-
# versionen", utan flaggan '-i', används. 









# såhär kompilerar vi nu! 
#g++ -std=c++11 -o pacman src/Pacman.cpp `sdl-config --cflags` `sdl-config --libs` -lSDL_image -lSDL_ttf
