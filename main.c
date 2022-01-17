#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>

#include "input.h"

bool eflag = false; //Opción -e, switch to english
bool iflag = false; //Opción -i, ingresa una línea de texto
bool aflag = false; //Opción -a, imprime argumentos en orden ascendente
bool dflag = false; //Opción -d, imprime argumentos en orden descendente

void print_help(char *command)
{
	printf("Programa en C ejemplo, imprime argumentos ingresados en consola.\n");
	printf("uso:\n %s [-i] [-e] [-a] [-d] [arg 1] [arg 2] ... [arg n]\n", command);
	printf(" %s -h\n", command);
	printf("Opciones:\n");
	printf(" -h\t\t\tAyuda, muestra este mensaje\n");
	printf(" -e\t\t\tSwitch to english\n");
	printf(" -i\t\t\tIngresa una línea de texto\n");
	printf(" -a\t\t\tImprime argumentos en orden ascendente\n");
	printf(" -d\t\t\tImprime argumentos en orden descendente\n");
}

void sort(char **text, int n){
	char *temp;
	bool instruccion;
	int i, j;

	if(aflag && dflag){
		printf("No se realizó el ordenamiento");
	}else{
		for(i=0; i<n; i++){
			for (j=i+1; j<n; j++){
				if(aflag){
		                        instruccion = strcmp(text[i],text[j]) > 0;
               			}else{
                       			instruccion = strcmp(text[i],text[j]) < 0;
               			}

				if (instruccion){
					temp = text[i];
					text[i] = text[j];
					text[j] = temp;
				}
			}
		}
	}
}

int main(int argc, char **argv)
{
	int opt, index;

	/* Este lazo recorre los argumentos buscando las
	opciones -e y -h... */
	while ((opt = getopt (argc, argv, "iehad")) != -1){
		switch(opt)
		{
			case 'i':
				iflag = true;
				break;
			case 'e':
				eflag = true;
				break;
			case 'a':
				aflag = true;
				break;
			case 'd':
				dflag = true;
				break;
			case 'h':
				print_help(argv[0]);
				return 0;
			case '?':
			default: 
				fprintf(stderr, "uso: %s [-i] [-e] [-a] [-d] [arg 1] [arg 2] ... [arg n]\n", argv[0]);
				fprintf(stderr, "     %s -h\n", argv[0]);
				return -1;
		}
	}

	// TODO: Sorting -a | -d
	sort( argv+optind , argc-optind );

	/* Aquí imprime argumentos que no son opción */
	// optind: indica el inicio de los argumentos sin opción
	for (index = optind; index < argc; index++) {
		if(eflag)
			printf ("Non-option argument: %s\n", argv[index]);
		else
			printf ("Argumento no-opción: %s\n", argv[index]);
	}

	/* Aquí ingresa una línea de texto desde consola y la reimprime en consola */
	if(iflag) {
		char *texto;
		get_from_console(&texto);
		printf("%s\n", texto);
		free(texto);
	}

	/* El programa se invocó sin usar opciones o argurmentos */
	if(argc == 1)
		print_help(argv[0]);
}

