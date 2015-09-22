#include "matrix.h"
#include <stdlib.h>

extern unsigned char proximo(unsigned char *a,
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
	unsigned int i, j;
	for (i = 0; i < self->size-1; ++i) {
		for (j = 0; j < self->size; ++j ) {
			unsigned char value = proximo(self->ptr, i, j, rule, self->size);
			Matrix_write(self, value, i+1, j);
		}
	}
}
