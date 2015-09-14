#include "matrix.h"
#include <stdlib.h>

unsigned char proximo126(Matrix* matrix, size_t i, size_t j, unsigned char rule);

void Matrix_create(Matrix* self, size_t size) {
	self->ptr = malloc(size*size);
	self->size = size;
}


void Matrix_write(Matrix* self, unsigned char value, size_t row, size_t column) {
	self->ptr[self->size*row + column] = value;
}

char Matrix_read(Matrix* self, size_t row, size_t column){
	return self->ptr[self->size*row + column];
}


void Matrix_destroy(Matrix* self) {
	free(self->ptr);
}

void Extend(Matrix* self, unsigned char rule) {
	for (size_t i = 0; i < self->size-1; ++i) {
		for (size_t j = 0; j < self->size; ++j ) {
			unsigned char value = proximo126(self, i, j, rule);
			Matrix_write(self, value, i+1, j);
		}
	}
}


unsigned char proximo126(Matrix* matrix, size_t i, size_t j, unsigned char rule) {
	unsigned char left, right, actual;
	if (j > 0) {
		left = Matrix_read(matrix, i, j-1);
	} else {
		left = Matrix_read(matrix, i, matrix->size - 1);
	}
	if (j != matrix->size - 1) {
		right = Matrix_read(matrix, i, j+1);
	} else {
		right = Matrix_read(matrix, i, 0);
	}
	actual = Matrix_read(matrix, i, j);

	int pos = right + actual*2 + left*4;
	unsigned char value = (rule << (8 - pos - 1));
	value = (value >> (8 - 1));

	return value;
}
