#include <stddef.h>

typedef struct {
	unsigned char* ptr;
	size_t size;
} Matrix;


/* Initializes the matrix with size */
void Matrix_create(Matrix* self, size_t size);

/* Write 'value' in self[row, column] */
void Matrix_write(Matrix* self, char value, size_t row, size_t column);

/* Returns the value of self[row, column] */
char Matrix_read(Matrix* self, size_t row, size_t column);

/* Copies the passed array in the specified row */
void Matrix_copy_row(Matrix* self, char* array, size_t row);

/* Destroys the matrix */
void Matrix_destroy(Matrix* self);