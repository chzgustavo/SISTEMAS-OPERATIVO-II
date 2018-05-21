#VARIABLES (compilador, flags y objects)
CC = gcc
CFLAGS = -Werror -Wall -pedantic
OBJ = tp2p.c 
#main.o fuente1.o fuente2.o



all: tp2p

#PUEDE IMPRIMIRSE MENSAJES AL USUARIO MEDIANTE "echo"
tp2p: tp2p.c
	${CC}   ${CFLAGS}  -o tp2p tp2p.c -lm -fopenmp
	



#DECLARARLA PHONY TIENE DOS VENTAJAS: Evita conflictos y mejor performance
clean:
	rm -rf *.o tp2p

