#include <ctype.h> //se incluye esta libreria porque se necesita la funcion toupper() que esta posee para la funcion posicion

int contarPalabras(char string[1000]) {   //cuenta las palabras depositadas en el string que se le pasa
	int palabras = 0;
	for (int i = 0; i < strlen(string); i++) {
		if (string[i] == '\n')  //cada palabra va a tener un \n, entonces contamos estos para saber la cantidad
			palabras++;
	}
	return palabras;   //retorna la cantidad de palabras
}

int posicion(char c, char alfa[27]){  //recibe un char y dice en que posicion del string alfa se encuentra
	int i=0;
	c = toupper(c); //transforma el char a mayuscula (en caso que venga en minuscula) para que por ejemplo "a" y "A" se consideren iguales
	while(i < 27){   //se recorre el string
		if (c == alfa[i]){   
			return i;   //en lo que consigue coincidencia devuelve el valor de la posicion de ese char en el string
		}
		else
			i++;     //mientras no lo consiga va sumando
	}
}

int comparar(char s1[1000],char s2[1000],char alfa[27]){ //esta funcion hace la misma funcion que "strcmp()" solo que con el alfabeto que se lee del archivo 
	int i = 0;
	while (i < strlen(s1) && i < strlen(s2)){
		if (posicion(s1[i],alfa) < posicion(s2[i],alfa))   
			return -1;
		else if (posicion(s2[i],alfa) < posicion(s1[i],alfa))
			return 1;
		else
			i++;                    //retorna lo mismo que "strcmp()", es decir:
	}								//-1: s1 es menor que s2, 0: son iguales, 1: s2 es menor que s1
	if (i < strlen(s2))
		return -1;
	else if (i < strlen(s1))
		return 1;
	else
		return 0;
}

void ordenamiento(char palabras[1000], char div1[1000], char div2[1000], char alfa[27]){  //recibe los strings que los hijos devuelven ordenados, el alfabeto y donde se van a fusionar los strings
	int i = 0, j = 0;  //estos contadores se recorreran div1 y div2
	int p=0, q=0;   //estos comp1 y comp2 queson strings que estan declarados mas abajo
	int primero = 1;  //indicador para saber si ya se introdujo el primer elemento a palabras
	char comp1[1000] = "", comp2[1000] = "";  //estos 2 strings sirven para depositar palabra por palabra de div1 y div2 y compararlas entre si
	strcpy(palabras,""); //se vacia el string palabras (se supone que las palabras estan repartidas ya en div1 y div2 ya ordenadas listas para reintroducirse en este string)
	while (div1[i] != '\n'){  //en este while lee la primera palabra en div1
		comp1[i] = div1[i];
		i++;
	}
	while (div2[j] != '\n'){ //en este while lee la primera palabra en div2
		comp2[j] = div2[j];
		j++;
	}    //ni comp1 ni comp2 van a tener \n, este problema se resulve luego
	while (i < strlen(div1) && j < strlen(div2)){  //se mantiene en el ciclo hasta que terminemos de recorrer div1 o div2
		if (comparar(comp1, comp2,alfa) <=0){  //compara las palabras en comp1 y comp2, dependiendo del resultado, se concatena comp1 o comp2 en palabras
			//aqui se va a concatenar comp1
			if (primero){	//caso por si es la primera palabra en entrar a palabras
				strcpy(palabras,comp1);
				primero--;
			}
			else{			//caso para cuando no es el priemro
				strcat(palabras,comp1);
			}
			strcat(palabras,"\n"); //como las variables "comp" no leen el \n se concatena este despues de concatenar cada "comp" (en este caso comp1)
			strcpy(comp1,"\0");  //se vacia comp1 para leer otra palabra
			p = 0;   //se posiciona p que recorrera comp1
			i++;	//se posiciona i un puesto despues del que estaba porque siempre se queda en un \n
			while (div1[i] != '\n' && i <= strlen(div1)){  //saldra del ciclo cuando se consiga un \n o i ya sea mayor que la longitud de div1
				comp1[p] = div1[i];
				i++;
				p++;
			}
		}
		else{   //este else tiene la misma logica que el caso del if, solo que aqui se trabaja con comp2, div2, q y j
			//aqui se va a concatenar comp2
			if(primero){
				strcpy(palabras,comp2);				
				primero--;
			}														//***Analogias con el if
			else{													//comp2->comp1  div2->div1  q->p  j->i
				strcat(palabras,comp2);
			}
			strcat(palabras,"\n");
			strcpy(comp2,"\0");
			q = 0;
			j++;
			while (div2[j] != '\n' && j <= strlen(div2)){
				comp2[q] = div2[j];
				j++;
				q++;
			}
		}
	}//cuando salga del while siempre quedaran elementos por agregar de div1 o div2, pero se entiende que estos se pueden meter facilmente al final de palabras por el ordenamiento previo
	if (i < strlen(div1)){  //en caso de que quede palabras por agregar de div1
		strcat(palabras,comp1); //si quedan por agregar de div1, es decir que tambien queda una en comp1, asi que se concatena
		strcat(palabras,"\n"); //se concatena su respectivo \n
		i++; //se posiciona a i en una posicion siguiente al \n en div1
		strcpy(comp1,""); //se vacia comp1
		p = 0;  //se posiciona p
		while(i <= strlen(div1)){ //se agrega 1 a 1 lo que queda de div1 en comp1
			comp1[p] = div1[i];
			p++;
			i++;
		}
		strcat(palabras,comp1); //se concatena comp1 a palabras
		//cabe acotar que aqui no hace falta concatenar un \n despues de comp1 porque ya lo leera en el while anterior
	}
	else{   //en caso de que quede palabras por agregar de div1
		strcat(palabras,comp2);
		strcat(palabras,"\n");
		j++;                                   //al igual que en el otro if else, este guarda la misma analogia entre si
		strcpy(comp2,"");					   //comp2->comp1  div2->div1  q->p  j->i
		q = 0;                                 //osea funciona igual solo que con diferentes variables
		while(j <= strlen(div2)){
			comp2[q] = div2[j];
			q++;
			j++;
		}
		strcat(palabras,comp2);
	}
}

void ordenar(char palabras[1000], int cant, char alfa[27]){   //funcion que se va a llamar desde el main, recibe las palabras leidas del archivo, la cantidad de estas y el alfabeto
	char string1[1000] = "";  //se declaran 2 strings para poder partir palabras en 2
	char string2[1000] = "";  //estos son los que se van a enviar a los procesos hijos (1 a cada uno)
	int j = 0;
	int caso;
	if (cant == 2){             //si la lista pasada tiene una longitud de 2, se ordena normalmente
		caso = 0;
		for (int i=0; i< strlen(palabras); i++) {  //se recorre todo el string palabras
			if (!caso) {//caso para la primera palabra
				string1[j] = palabras[i];
				if (palabras[i] == '\n'){
					caso = 1;
					j = 0;
				}
				else
					j++;
			}
			else { //caso para la segunda palabra
				string2[j] = palabras[i];
				j++;
			}
		}
		if (comparar(string1, string2,alfa) <= 0){  //se llama a comparar para saber como depositar los strings en palabras
			strcpy(palabras,string1);
			strcat(palabras,string2);
		}
		else{
			strcpy(palabras,string2);
			strcat(palabras,string1);
		}
	}
	else{            //si no, entra por aca para dividir palabras y crear a los hijos que organicen estos 2 strings
		int cont = 0; //estas variables son para separar palabras en string1 y string2 equitativamente
		int q = 0;
		caso = 0;
		for (int i=0; i< strlen(palabras); i++) {
			if (!caso) {
				string1[j] = palabras[i];
				if (palabras[i] == '\n'){
					cont++;
					if(cont == (cant/2)){
						j = 0;
						caso = 1;
					}
				}
			}
			else {
				string2[q] = palabras[i];
				q++;
			}
			j++;
		}
		//ya con string1 y string2 listos declaramos lo que necesitamos para los procesos
	// --------------------------------------------- procesos ------------------------------------------------------ ||
		int estado, h1_end = 0, h2_end = 0; //los estados de los hijos
		int pipe1[2];  //los pipes utilizados
		int pipe2[2];
		pipe(pipe1);
		pipe(pipe2);
		pid_t pid_padre, pid_hijo1, pid_hijo2;
		if ((pid_hijo1 = fork()) == 0){
			//Proceso hijo izquierda
			close(pipe1[0]);		
			ordenar(string1, contarPalabras(string1), alfa);
			write(pipe1[1], string1, 1000);
			close(pipe1[1]);
			exit (0);	
		}
		else if ((pid_hijo2 = fork()) == 0) {
			//Proceso hijo derecha
			close(pipe2[0]);		
			ordenar(string2, contarPalabras(string2), alfa);
			write(pipe2[1], string2, 1000);
			close(pipe2[1]);	
			exit (0);	
		}
		else { 
			//Proceso padre			
			while((!h1_end) || (!h2_end)){
				/* Espero información sobre cualquier hijo*/
				int pid;
				pid = wait(&estado);
			
				/* Me fijo quien terminó y cambio la variable de estado. */
				if (pid == pid_hijo1)
					h1_end = 1;
				if (pid == pid_hijo2)
					h2_end = 1;
			}

			/* Terminaron los dos hijos */
			close(pipe1[1]);
			close(pipe2[1]); 
			read(pipe1[0], string1, 1000);
			read(pipe2[0], string2, 1000);
			ordenamiento(palabras,string1,string2, alfa);
			close(pipe1[0]);
			close(pipe2[0]);		
		}
	}
}