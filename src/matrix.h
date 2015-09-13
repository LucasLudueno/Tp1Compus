typedef struct {
	unsigned char* ptr;
	unsigned int size;
} Matrix;


/* Initializes the matrix with size */
void Matrix_create(Matrix* self, unsigned int size);

/* Destroys the matrix */
void Matrix_destroy(Matrix* self);