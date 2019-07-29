/* Proyecto I----Sistemas de Operación

Integrantes:
Alexander Fernandez           C.I: 26.530.106
Luis Fuentes                  C.I: 26.483.209
Rafael Mendez                 C.I: 26.483.231
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include "EPipeM.h"

int main(int arg, char *args[]){
		
	char palabras[1000] = ""; //string donde se leeran todas las frase
	char respa[4] = ""; //string que ayudara a leer el archivo del alfabeto
	char resp[1000] = "";	//string que ayudara a leer el archivo de las palabras
	char alfabeto[27] = "";	 //string donde se guardará el alfabeto
	int j = 0;
	//-------------------------------------Lectura de archivos------------------------------------
	//Lectura del alfabeto
	FILE *B = fopen(args[1], "r"); 
	while (!feof(B)){
		fgets(respa, 4, B);
		alfabeto[j] = respa[0];
		j++;
	}
	fclose(B);
	alfabeto[26] = '\0';
	//lectura de las palabras
	FILE *A = fopen(args[2], "r");
	int cont = 0;
	while (!feof(A)) {
		fgets(resp, 1000, A);
		cont++;
	}
	strcpy(resp,"");
	fclose(A);
	cont--;
	A = fopen(args[2], "r");
	for (int i = 0; i < cont; i++){
		fgets(resp, 1000, A);
		if (i)
			strcat(palabras,resp);
		else
			strcpy(palabras,resp);
	}
	fclose(A);
	//---------------------------------------------------------------------------------------------
	printf("\nAlfabeto de guia para ordenar: %s\n\n",alfabeto);
	printf("Palabras desordenadas: \n%s\n", palabras);	
	ordenar(palabras,contarPalabras(palabras),alfabeto);	
	int caso = 1;
	printf("Palabras ordenadas: \n");	
	//el siguiente ciclo es para poder imprimir bien el string palabras cuando se termina de ordenar
	for(int r = 0; r < strlen(palabras); r++){
			if (caso) {
				printf(".      ---> ");
				caso = 0;
			}			
			printf("%c", palabras[r]);
			if (palabras[r] == '\n' && r < strlen(palabras) - 1)
				printf(".      ---> ");
		}	
	printf("\n\n");
	return 0;
}