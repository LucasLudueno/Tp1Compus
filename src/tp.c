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

void loadMatrix(Matrix* matrix, FILE* input);

int main(int argc, char** argv) {

	FILE *fileInput;
	FILE *fileOutput;
	unsigned char rule;
	unsigned int size;
	char help[] = HELPCODE;
	char version[] = VERSIONCODE;

	if ( !strcmp(argv[1], help) ) {		// HAY ALGUNA FORMA DE PONERLO MAS LINDO ESTO ?
		printf("Uso: \n");
		printf("autcel -h\n");
		printf("autcel -V \n");
		printf("autcel R N inputfile [-o outputprefix]\n");
		printf("Opciones: \n");
		printf("-h, --help	Imprime este mensaje.\n");
		printf("-V, --version	Da la versión del programa.\n");
		printf("-o  Prefijo de los archivos de salida.\n");
		printf("Ejemplos:\n");
		printf("autcel 30 80 inicial -o evolucion\n");
		printf("Calcula la evolucion del automata Regla 30\n");
		printf("en un mundo unidimensional de 80 celdas, por 80 iteraciones.\n");
		printf("El archivo de salida se llamara evolucion.pbm.\n");
		printf("Si no se da un prefijo para los archivos de salida,\n");
		printf("el prefijo será el nombre del archivo de entrada.\n");
		return 0;
	} else if ( !strcmp(argv[1], version) ) {
		printf("Autcel Version C\n");
		return 0;
	}

	rule = atoi(argv[1]);
	size = atoi(argv[2]);

	fileInput = fopen( argv[3], "r");
	if (argc > 4) {
		fileOutput = fopen(strcat(argv[5],".pbm"), "w+");
	} else {
		fileOutput = fopen(strcat(argv[3],".pbm"), "w+");
	}

	Matrix* matrix = malloc(sizeof(Matrix));
	Matrix_create(matrix, size);

	printf("Leyendo estado inicial...\n");
	loadMatrix(matrix, fileInput);
	Extend(matrix, rule);
	printf("Grabando %s.pbm\n","NOMBRE DEL ARCHIVO");
	writePbmImage(matrix, size, fileOutput);
	printf("Listo\n");

	Matrix_destroy(matrix);
	fclose(fileInput);
	fclose(fileOutput);
	return 0;
}


void writePbmImage(Matrix* matrix, unsigned int n, FILE *file) {
	int width = PIXELWIDTH;
	int height = PIXELHEIGHT;

	fprintf(file, "%s\n", MAGICNUMBER);						// Header
	fprintf(file, "%d %d\n", n*PIXELWIDTH, n*PIXELHEIGHT); 	// Width and Height

	for (int i = 0; i < n; ++i) {							// Writing the image
		for (int pixY = 0; pixY < height; ++pixY) {
			for (int j = 0; j < n; ++j) {
				for (int pixX = 0; pixX < width; ++pixX) {
					unsigned char value = Matrix_read(matrix, i, j);
					fprintf(file, "%d ", value);
				}
			}
			putc('\n',file);
		}
	}
}


void loadMatrix(Matrix* matrix, FILE* input) {
	for(int j=0; j < matrix->size; ++j) {
		char c = fgetc(input);
		unsigned char cell = atoi(&c);
		Matrix_write(matrix, cell, 0, j);
	}
}
