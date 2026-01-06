all: grafo.o main.o
	@gcc grafo.o main.o -o exe
	@rm -r grafo.o main.o
grafo.o: grafo.c
	@gcc grafo.c -c -Wall
main.o: main.c
	@gcc main.c -c -Wall
run:
	@./exe
