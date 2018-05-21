#VARIABLES (compilador, flags y objects)
CC = gcc
CFLAGS = -Werror -Wall -pedantic
OBJ = tp2sp.c 
#main.o fuente1.o fuente2.o



all: tp2sp

#PUEDE IMPRIMIRSE MENSAJES AL USUARIO MEDIANTE "echo"
tp2sp: tp2sp.c
	${CC}   ${CFLAGS}  -o tp2sp tp2sp.c -lm -fopenmp
	



#DECLARARLA PHONY TIENE DOS VENTAJAS: Evita conflictos y mejor performance
clean:
	rm -rf *.o tp2sp

