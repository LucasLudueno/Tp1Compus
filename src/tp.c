#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "matrix.h"

#define PIXELWIDTH 4
#define PIXELHEIGHT 4
#define MAGICNUMBER "P1"

#define HELPCODE "-h"
#define VERSIONCODE "-V"

void writePbmImage(Matrix* matrix, unsigned int n, FILE *file);

int loadMatrix(Matrix* matrix, FILE* input);

void printHelpMenu();

int main(int argc, char** argv) {

	if (argc < 2) {
		printHelpMenu();
		return EXIT_FAILURE;
	}

	FILE *fileInput;
	FILE *fileOutput;
	unsigned char rule;
	unsigned int size;
	char help[] = HELPCODE;
	char version[] = VERSIONCODE;

	if ( !strcmp(argv[1], help) ) {
		printHelpMenu();
		return EXIT_SUCCESS;
	} else if ( !strcmp(argv[1], version) ) {
		printf("Autcel Version C\n");
		return EXIT_SUCCESS;
	}

	rule = atoi(argv[1]);
	size = atoi(argv[2]);

	Matrix matrix;
	Matrix_create(&matrix, size);

	fileInput = fopen( argv[3], "r");
	printf("Leyendo estado inicial...\n");
	if ( loadMatrix(&matrix, fileInput) == EXIT_FAILURE) {
		fprintf(stderr,"%s","Archivo de entrada erroneo\n");
		Matrix_destroy(&matrix);
		return EXIT_FAILURE;
	}

	char* fileOutputName;
	if (argc > 4) {
		fileOutputName = argv[5];
		fileOutput = fopen(strcat(argv[5],".pbm"), "w+");
	} else {
		fileOutputName = argv[3];
		fileOutput = fopen(strcat(argv[3],".pbm"), "w+");
	}

	Extend(&matrix, rule);
	printf("Grabando %s\n",fileOutputName);
	writePbmImage(&matrix, size, fileOutput);
	printf("Listo\n");

	Matrix_destroy(&matrix);
	fclose(fileInput);
	fclose(fileOutput);
	return EXIT_SUCCESS;
}


void writePbmImage(Matrix* matrix, unsigned int n, FILE *file) {
	int width = PIXELWIDTH;
	int height = PIXELHEIGHT;

	fprintf(file, "%s\n", MAGICNUMBER);						// Header
	fprintf(file, "%d %d\n", n*PIXELWIDTH, n*PIXELHEIGHT); 	// Width and Height

	int i, pixY, j, pixX;
	for (i = 0; i < n; ++i) {							// Writing the image
		for (pixY = 0; pixY < height; ++pixY) {
			for (j = 0; j < n; ++j) {
				for (pixX = 0; pixX < width; ++pixX) {
					unsigned char value = Matrix_read(matrix, i, j);
					fprintf(file, "%d ", value);
				}
			}
			putc('\n',file);
		}
	}
}


int loadMatrix(Matrix* matrix, FILE* input) {
	int j;
	for(j = 0; j < matrix->size; ++j) {
		char c = fgetc(input);
		unsigned char cell = atoi(&c);
		if (cell != 0 && cell != 1 ) {
			return 1;
		}
		Matrix_write(matrix, cell, 0, j);
	}
	fgetc(input);
	if (fgetc(input) != EOF) {
		return 1;
	}
	return 0;
}


void printHelpMenu() {
	printf("Uso: \n");
	printf("\tautcel -h\n");
	printf("\tautcel -V \n");
	printf("\tautcel R N inputfile [-o outputprefix]\n");
	printf("Opciones: \n");
	printf("\t-h, --help	Imprime este mensaje.\n");
	printf("\t-V, --version	Da la versión del programa.\n");
	printf("\t-o  Prefijo de los archivos de salida.\n");
	printf("Ejemplos:\n");
	printf("\tautcel 30 80 inicial -o evolucion\n");
	printf("\tCalcula la evolucion del automata Regla 30\n");
	printf("\ten un mundo unidimensional de 80 celdas, por 80 iteraciones.\n");
	printf("\tEl archivo de salida se llamara evolucion.pbm.\n");
	printf("\tSi no se da un prefijo para los archivos de salida,\n");
	printf("\tel prefijo será el nombre del archivo de entrada.\n");
}