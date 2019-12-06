
OB += \
fonctions.o \
main.o
	

%.o:
	g++  -O0 -g3 -Wall -c fonctions.cpp  main.cpp `pkg-config --cflags --libs opencv`

all:$(OB)
	@echo 'Building target: $@'
	g++  -o "tp3" $(OB)  `pkg-config --cflags --libs opencv`
	@echo 'Finished building target: $@'

clear:
	rm -rf *.o

mproper: clean
	rm -rf $(OB) fonctions

