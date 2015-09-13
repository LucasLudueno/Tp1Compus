#include "matrix.h"
#include <stdlib.h>


void Matrix_create(Matrix* self, size_t size) {
	self->ptr = malloc(size*size);
	self->size = size;
}


void Matrix_write(Matrix* self, char value, size_t row, size_t column) {
	self->ptr[self->size*row + column] = value;
}


char Matrix_read(Matrix* self, size_t row, size_t column) {
	return self->ptr[self->size*row + column];
}


void Matrix_copy_row(Matrix* self, char* array, size_t row) {
	for(int j = 0; j < self->size; ++j) {
		Matrix_write(self, array[j], row, j);
	}
}


void Matrix_destroy(Matrix* self) {
	free(self->ptr);
}