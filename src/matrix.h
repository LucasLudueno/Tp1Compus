typedef struct {
	unsigned char* ptr;
	size_t size;
} Matrix;


/* Initializes the matrix with size */
void Matrix_create(Matrix* self, size_t size);

/* Write 'value' in self[row, column] */
void Matrix_write(Matrix* self, char value, size_t row, size_t column);

/* Destroys the matrix */
void Matrix_destroy(Matrix* self);