all: main.o Manazer.o Kocka.o HraciaPlocha.o Hrac.o Figurka.o Tcp_server.o Tcp_client.o
	g++ main.o Manazer.o Kocka.o HraciaPlocha.o Hrac.o Figurka.o Tcp_server.o Tcp_client.o -o CNS_App

main.o: main.cpp
	g++ -c main.cpp

Tcp_server.o: Tcp_server.cpp
	g++ -c Tcp_server.cpp

Tcp_client.o : Tcp_client.cpp
	g++ -c Tcp_client.cpp

Manazer.o: Manazer.cpp Manazer.h
	g++ -c Manazer.cpp

Kocka.o: Kocka.cpp Kocka.h
	g++ -c Kocka.cpp

HraciaPlocha.o: HraciaPlocha.cpp HraciaPlocha.h
	g++ -c HraciaPlocha.cpp

Hrac.o: Hrac.cpp Hrac.h
	g++ -c Hrac.cpp

Figurka.o: Figurka.cpp Figurka.h
	g++ -c Figurka.cpp

clean:
	rm *.o main
