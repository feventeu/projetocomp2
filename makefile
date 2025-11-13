CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g
OBJ = main.o pergunta.o arquivo.o menu.o jogo.o

all: jogo

jogo: $(OBJ)
	$(CC) $(CFLAGS) -o jogo $(OBJ)

main.o: main.c pergunta.h menu.h
	$(CC) $(CFLAGS) -c main.c

pergunta.o: pergunta.c pergunta.h
	$(CC) $(CFLAGS) -c pergunta.c

arquivo.o: arquivo.c arquivo.h pergunta.h
	$(CC) $(CFLAGS) -c arquivo.c

menu.o: menu.c menu.h arquivo.h pergunta.h jogo.h
	$(CC) $(CFLAGS) -c menu.c

jogo.o: jogo.c jogo.h pergunta.h
	$(CC) $(CFLAGS) -c jogo.c

run: jogo
	./jogo

clean:
	rm -f *.o jogo

.PHONY: all run clean
