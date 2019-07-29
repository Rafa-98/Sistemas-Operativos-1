all: ordenar

ordenar: Main.c EPipeM.h
	gcc Main.c -o ordenar

clean:
	rm -f ordenar
