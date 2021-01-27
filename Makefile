#sur all: on a une dependance ClassDatagrammeUDp.o du coup on doit compiler la cible ClassDatagrammeUDP.o
all: ClassDatagrammeUDP.o test.o
	g++ ClassDatagrammeUDP.o test.o -o ProgramTest -g


#Création de nos fichiers .o
ClassDatagrammeUDP.o: ClassDatagrammeUDP.cpp ClassDatagrammeUDP.h
	g++ -g -c ClassDatagrammeUDP.cpp


#compile de la cible test.o
test.o: test.cpp
	g++ -g -c test.cpp

clean:
	rm -rf *.o
