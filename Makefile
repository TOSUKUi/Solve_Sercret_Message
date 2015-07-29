Protocol.out: Protocol.o Sha256.o
	gcc-5 -O0  -o Protocol.out Protocol.o Sha256.o  

Protocol.o:Protocol.c
	gcc-5 -c -g Protocol.c

Sha256.o:Sha256.c
	gcc-5 -c -g Sha256.c
