#
# Makefil f�r att kompilera pacman med g++
#
# 

# Diagnosmeddelanden fr�n kompilatorn (g++) filtreras av gccfilter
CCC = gccfilter -c -a g++

# Kompilatorflaggor, l�gg till '-g' om kompilering f�r avlusning ska g�ras 
CCFLAGS += -std=c++11 `sdl-config --cflags` `sdl-config --libs` -lSDL_image -lSDL_ttf

# Preprocessorflaggor, -I l�gger till en filkatalog i inkluderingss�kv�gen.
CPPFLAGS += -I$(src)


# Objektkodsmoduler som ing�r i det kompletta spelet.
OBJECTS = Pacman.o

# Huvudm�l - skapas med kommandot 'make' eller 'make pacman'.
Pacman: $(OBJECTS) makefile
	$(CCC) $(CPPFLAGS) $(CCFLAGS) $(LDFLAGS) -o test $(OBJECTS)

# Delm�l (flaggan -c avbryter innan l�nkning, objektkodsfil erh�lls)
Pacman.o: src/Pacman.cpp
	$(CCC) $(CPPFLAGS) $(CCFLAGS) -c src/Pacman.cpp


# 'make clean' tar bort objektkodsfiler och 'core' (minnesdump).
clean:
	@ \rm -rf *.o *.gch core

# 'make zap' tar �ven bort det k�rbara programmet och reservkopior (filer
# som slutar med tecknet '~').
zap: clean
	@ \rm -rf test *~

# Se upp vid eventuell �ndring, '*' f�r absolut inte finnas f�r sig!!!
#
# '@' medf�r att kommandot inte skrivs ut p� sk�rmen d� det utf�rs av make.
# 'rm' �r ett alias f�r 'rm -i' p� IDA:s system, '\rm' inneb�r att "original-
# versionen", utan flaggan '-i', anv�nds. 









# s�h�r kompilerar vi nu! 
#g++ -std=c++11 -o pacman src/Pacman.cpp `sdl-config --cflags` `sdl-config --libs` -lSDL_image -lSDL_ttf
