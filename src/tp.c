#include <stdio.h>
#include "matrix.h"

#define PIXELWIDTH 4
#define PIXELHEIGHT 4
#define MAGICNUMBER "P1"

void writePbmImage(unsigned char* matrix, unsigned int n, FILE *file);

void loadMatrix(Matrix* matrix, FILE* input);

int main(int argc, char** argv) {

	FILE *fileInput;
	FILE *fileOutput;
	//unsigned int rule;
	unsigned int size;
	char help[] = HELPCODE;
	char version[] = VERSIONCODE;

	if ( !strcmp(argv[1], help) ) {
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

	//rule = atoi(argv[1]);
	size = atoi(argv[2]);
	unsigned char matrix[size*size];

	fileInput = fopen( strcat (argv[3],".txt"), "r");
	if (argc > 4) {
		fileOutput = fopen( strcat (argv[5],".pbm"), "w+");
	} else {
		fileOutput = fopen( strcat (argv[3],".pbm"), "w+");
	}

	matrix[0] = '0';
	matrix[1] = '0';
	matrix[2] = '0';
	matrix[3] = '0';
	matrix[4] = '0';
	matrix[5] = '1';
	matrix[6] = '0';
	matrix[7] = '0';
	matrix[8] = '0';
	matrix[9] = '1';
	matrix[10] = '1';
	matrix[11] = '0';
	matrix[12] = '0';
	matrix[13] = '0';
	matrix[14] = '0';
	matrix[15] = '0';

	writePbmImage(matrix, size, fileOutput);
	fclose(fileInput);
	fclose(fileOutput);
	return 0;
}


void writePbmImage(unsigned char* matrix, unsigned int n, FILE *file) {
	int width = PIXELWIDTH;
	int height = PIXELHEIGHT;

	fprintf(file, "%s\n", MAGICNUMBER);						// Header
	fprintf(file, "%d %d\n", n*PIXELWIDTH, n*PIXELHEIGHT); 	// Width and Height

	for (int i = 0; i < n; ++i) {							// Writing the image
		for (int pixY = 0; pixY < height; ++pixY) {
			for (int j = 0; j < n; ++j) {
				for (int pixX = 0; pixX < width; ++pixX) {
					unsigned int pos = n*i + j;
					fprintf(file, "%c ", matrix[ pos ]);
				}
			}
			putc('\n',file);
		}
	}
}


void loadMatrix(Matrix* matrix, FILE* input) {
	for(int i=0; i < matrix->size; ++i) {
		char cell = fgetc(input);
		Matrix_write(matrix, cell, 0, i);
	}
}
