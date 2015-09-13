#include <stdio.h>

#define PIXELWIDTH 4
#define PIXELHEIGHT 4
#define MAGICNUMBER "P1"

void writePbmImage(unsigned char* matrix, unsigned int n, FILE *file);

int main(int argc, char** argv) {

	unsigned int size = 4;
	unsigned char matrix[size*size];

	matrix[0] = '0';
	matrix[1] = '0';
	matrix[2] = '0';
	matrix[3] = '0';
	matrix[4] = '0';
	matrix[5] = '1';
	matrix[6] = '0';
	matrix[7] = '0';
	matrix[8] = '0';
	matrix[9] = '1';
	matrix[10] = '1';
	matrix[11] = '0';
	matrix[12] = '0';
	matrix[13] = '0';
	matrix[14] = '0';
	matrix[15] = '0';

	FILE *file = fopen("prueba.pbm", "w+");
	writePbmImage(matrix, size, file);
	fclose(file);
	return 0;
}


void writePbmImage(unsigned char* matrix, unsigned int n, FILE *file) {
	int width = PIXELWIDTH;
	int height = PIXELHEIGHT;

	fprintf(file, "%s\n", MAGICNUMBER);						// Header
	fprintf(file, "%d %d\n", n*PIXELWIDTH, n*PIXELHEIGHT); 	// Width and Height

	for (int i = 0; i < n; ++i) {							// Writing the image
		for (int pixY = 0; pixY < height; ++pixY) {
			for (int j = 0; j < n; ++j) {
				for (int pixX = 0; pixX < width; ++pixX) {
					unsigned int pos = n*i + j;
					fprintf(file, "%c ", matrix[ pos ]);
				}
			}
			putc('\n',file);
		}
	}
}
