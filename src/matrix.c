#include "matrix.h"
#include <stdlib.h>

unsigned char proximo(unsigned char *a,
					  unsigned int i, unsigned int j,
					  unsigned char regla, unsigned int N);

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
	for (unsigned int i = 0; i < self->size-1; ++i) {
		for (unsigned int j = 0; j < self->size; ++j ) {
			unsigned char value = proximo(self->ptr, i, j, rule, self->size);
			Matrix_write(self, value, i+1, j);
		}
	}
}

unsigned char proximo(unsigned char *a,
					  unsigned int i, unsigned int j,
					  unsigned char regla, unsigned int N) {
	unsigned char left, right, actual;
	if (j > 0) {
		left = *(a + i*N + j-1);
	} else {
		left = *(a + i*N + N-1);
	}
	if (j != N-1) {
		right = *(a + i*N + j+1);
	} else {
		right = *(a + i*N);
	}
	actual = *(a + i*N + j);

	int pos = right + actual*2 + left*4;
	unsigned char value = (regla << (8 - pos - 1));
	value = (value >> (8 - 1));

	return value;
}
