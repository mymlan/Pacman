
# Makefil för att kompilera pacman med g++
#
# 
# Diagnosmeddelanden från kompilatorn (g++) filtreras av gccfilter
CCC = g++

# Kompilatorflaggor, lägg till '-g' om kompilering för avlusning ska göras 
CCFLAGS += -std=c++11 `sdl-config --cflags` `sdl-config --libs` -lSDL_image -lSDL_ttf

OBJECTS = main.o sprite.o timer.o menu.o food.o score.o highscore.o pacman.o ghost.o string_input.o map_data.o board.o

# Huvudmål - skapas med kommandot 'make' eller 'make pacman'.
main: $(OBJECTS)
	$(CCC) -o pacman $(OBJECTS) $(CCFLAGS) 

# Delmål (flaggan -c avbryter innan länkning, objektkodsfil erhålls)

main.o: src/main.cpp  
	$(CCC) -c src/main.cpp $(CCFLAGS)
# 'make clean' tar bort objektkodsfiler och 'core' (minnesdump).


sprite.o: src/sprite.cpp src/sprite.h
	$(CCC) -c src/sprite.cpp $(CCFLAGS) 
# 'make clean' tar bort objektkodsfiler och 'core' (minnesdump).


timer.o: src/timer.cpp src/timer.h 
	$(CCC) -c src/timer.cpp $(CCFLAGS)
# 'make clean' tar bort objektkodsfiler och 'core' (minnesdump).

menu.o: src/menu.cpp src/menu.h
	$(CCC) -c src/menu.cpp $(CCFLAGS)
# 'make clean' tar bort objektkodsfiler och 'core' (minnesdump).

food.o: src/food.cpp src/food.h
	$(CCC) -c src/food.cpp $(CCFLAGS)
# 'make clean' tar bort objektkodsfiler och 'core' (minnesdump).

score.o: src/score.cpp src/score.h
	$(CCC) -c src/score.cpp $(CCFLAGS)
# 'make clean' tar bort objektkodsfiler och 'core' (minnesdump).

highscore.o: src/highscore.cpp src/highscore.h
	$(CCC) -c src/highscore.cpp $(CCFLAGS)
# 'make clean' tar bort objektkodsfiler och 'core' (minnesdump).

pacman.o: src/pacman.cpp src/pacman.h
	$(CCC) -c src/pacman.cpp $(CCFLAGS)
# 'make clean' tar bort objektkodsfiler och 'core' (minnesdump).

ghost.o: src/ghost.cpp src/ghost.h
	$(CCC) -c src/ghost.cpp $(CCFLAGS)
# 'make clean' tar bort objektkodsfiler och 'core' (minnesdump).

string_input.o: src/string_input.cpp src/string_input.h
	$(CCC) -c src/string_input.cpp $(CCFLAGS)
# 'make clean' tar bort objektkodsfiler och 'core' (minnesdump).

map_data.o: src/map_data.cpp src/map_data.h
	$(CCC) -c src/map_data.cpp $(CCFLAGS)
# 'make clean' tar bort objektkodsfiler och 'core' (minnesdump).

board.o: src/board.cpp src/board.h
	$(CCC) -c src/board.cpp $(CCFLAGS) 
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
