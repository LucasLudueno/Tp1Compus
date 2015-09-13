#include "matrix.h"
#include <stdlib.h>


void Matrix_create(Matrix* self, size_t size) {
	self->ptr = malloc(size*size);
	self->size = size;
}


void Matrix_write(Matrix* self, char value, size_t row, size_t column) {
	self->ptr[self->size*row + column] = value;
}


void Matrix_destroy(Matrix* self) {
	free(self->ptr);
}