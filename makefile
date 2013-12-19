
# Makefil f�r att kompilera pacman med g++
#
# 
# Diagnosmeddelanden fr�n kompilatorn (g++) filtreras av gccfilter
CCC = g++

# Kompilatorflaggor, l�gg till '-g' om kompilering f�r avlusning ska g�ras 
CCFLAGS += -std=c++11 `sdl-config --cflags` `sdl-config --libs` -lSDL_image -lSDL_ttf

OBJECTS = main.o sprite.o timer.o menu.o food.o score.o highscore.o pacman.o ghost.o string_input.o

# Huvudm�l - skapas med kommandot 'make' eller 'make pacman'.
main: $(OBJECTS)
	$(CCC) $(CCFLAGS) -o pacman $(OBJECTS)

# Delm�l (flaggan -c avbryter innan l�nkning, objektkodsfil erh�lls)

main.o: src/main.cpp  
	$(CCC) $(CCFLAGS) -c src/main.cpp
# 'make clean' tar bort objektkodsfiler och 'core' (minnesdump).


sprite.o: src/sprite.cpp src/sprite.h
	$(CCC) $(CCFLAGS) -c src/sprite.cpp
# 'make clean' tar bort objektkodsfiler och 'core' (minnesdump).


timer.o: src/timer.cpp src/timer.h 
	$(CCC) $(CCFLAGS) -c src/timer.cpp
# 'make clean' tar bort objektkodsfiler och 'core' (minnesdump).

menu.o: src/menu.cpp src/menu.h
	$(CCC) $(CCFLAGS) -c src/menu.cpp
# 'make clean' tar bort objektkodsfiler och 'core' (minnesdump).

food.o: src/food.cpp src/food.h
	$(CCC) $(CCFLAGS) -c src/food.cpp
# 'make clean' tar bort objektkodsfiler och 'core' (minnesdump).

score.o: src/score.cpp src/score.h
	$(CCC) $(CCFLAGS) -c src/score.cpp
# 'make clean' tar bort objektkodsfiler och 'core' (minnesdump).

highscore.o: src/highscore.cpp src/highscore.h
	$(CCC) $(CCFLAGS) -c src/highscore.cpp
# 'make clean' tar bort objektkodsfiler och 'core' (minnesdump).

pacman.o: src/pacman.cpp src/pacman.h
	$(CCC) $(CCFLAGS) -c src/pacman.cpp
# 'make clean' tar bort objektkodsfiler och 'core' (minnesdump).

ghost.o: src/ghost.cpp src/ghost.h
	$(CCC) $(CCFLAGS) -c src/ghost.cpp
# 'make clean' tar bort objektkodsfiler och 'core' (minnesdump).

string_input.o: src/string_input.cpp src/string_input.h
	$(CCC) $(CCFLAGS) -c src/string_input.cpp
# 'make clean' tar bort objektkodsfiler och 'core' (minnesdump).



clean:
	@ \rm -rf *.o *.gch pacman

# 'make zap' tar �ven bort det k�rbara programmet och reservkopior (filer
# som slutar med tecknet '~').
zap: clean
	@ \rm -rf pacman *~

# Se upp vid eventuell �ndring, '*' f�r absolut inte finnas f�r sig!!!
#
# '@' medf�r att kommandot inte skrivs ut p� sk�rmen d� det utf�rs av make.
# 'rm' �r ett alias f�r 'rm -i' p� IDA:s system, '\rm' inneb�r att "original-
# versionen", utan flaggan '-i', anv�nds. 
