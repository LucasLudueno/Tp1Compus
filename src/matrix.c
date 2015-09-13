#include "matrix.h"
#include <stdlib.h>


void Matrix_create(Matrix* self, unsigned int size) {
	self->ptr = malloc(size*size);
	self->size = size;
}

void Matrix_destroy(Matrix* self) {
	free(self->ptr);
}