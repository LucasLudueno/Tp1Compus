#include <stddef.h>

typedef struct {
	unsigned char* ptr;
	size_t size;
} Matrix;


/* Initializes the matrix with size */
void Matrix_create(Matrix* self, size_t size);

/* Write 'value' in self[row, column] */
void Matrix_write(Matrix* self, unsigned char value, size_t row, size_t column);

/* Destroys the matrix */
void Matrix_destroy(Matrix* self);

/* Read 'value" in self[row, colum] */
char Matrix_read(Matrix* self, size_t row, size_t column);

/* Extends the matrix from a rule */
void Extend(Matrix* self, unsigned char rule);
