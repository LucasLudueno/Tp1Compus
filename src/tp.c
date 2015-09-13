#include <stdio.h>
#include "matrix.h"

#define PIXELWIDTH 4
#define PIXELHEIGHT 4
#define MAGICNUMBER "P1"

void writePbmImage(unsigned char* matrix, unsigned int n, FILE *file);

void loadMatrix(Matrix* matrix, FILE* input);

char proximo126(Matrix* matrix, size_t i, size_t j);


int main(int argc, char** argv) {
	// Initializations: 
	unsigned int size = 4;
	Matrix matrix;
	Matrix_create(&matrix, size);
	FILE* inputFile = fopen("input", "r");
	loadMatrix(&matrix, inputFile);

	// Processing:
	char aux[size];
	for(int timestamp = 1; timestamp < size; ++timestamp) {
		for(int col = 0; col < size; ++col) {
			aux[col] = proximo126(&matrix, timestamp, col);
		}
		Matrix_copy_row(&matrix, aux, timestamp);
	}

	// Writing the output:
	FILE *file = fopen("prueba.pbm", "w+");
	writePbmImage(matrix.ptr, size, file);
	fclose(file);

	Matrix_destroy(&matrix);
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

char proximo126(Matrix* matrix, size_t i, size_t j) {
	char left, right, actual;
	if (j > 0) {
		left = Matrix_read(matrix, i-1, j-1);
	} else {
		left = Matrix_read(matrix, i-1, matrix->size - 1);
	}
	if (j != matrix->size - 1) {
		right = Matrix_read(matrix, i-1, j+1);
	} else {
		right = Matrix_read(matrix, i-1, 0);
	}
	actual = Matrix_read(matrix, i-1, j);
	if (left == right && left == actual && right == actual)
		return '0';
	else
		return '1';
}