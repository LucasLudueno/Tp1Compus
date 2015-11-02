#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include "matrix.h"

#define PIXELWIDTH 4
#define PIXELHEIGHT 4
#define MAGICNUMBER "P1"

#define EXIT_SUCCESS 0
#define INPUT_ERROR 1
#define PROCESSING -1
#define INVALID_OPTION -2
#define NO_OPTIONS -3
#define ERR_CANT_ARGS -4
#define SALIDA_TERMINAL 1


void writePbmImage(Matrix* matrix, unsigned int n, FILE *file);

int loadMatrix(Matrix* matrix, FILE* input);

// Funcion que imprime la ayuda del programa 
int printHelp(FILE* streamSalida);

// Funcion que imprime la version del programa 
int printVersion(FILE* streamSalida);

// Funcion que valida los argumentos de -o  
int validar(FILE* streamSalida, int argc, char** argv);

// Funcion que imprime cuando es una opcion no reconocida por el programa  
int invalidOpt(FILE* streamSalida);

int main(int argc, char** argv) {

    FILE *fileInput = NULL;
    FILE *fileOutput = NULL;
    char* fileOutputName = NULL;
    char* fileInputName = NULL;
    unsigned char rule = 0;
    unsigned int size = 0;
    int option = 0;
    int terminal = 0;
    int estado = 0;
    const char* opcionesCortas = "Vhto::"; // o tiene un arg. opcional
    const struct option opcionesLargas[] = {
        { "version", 0, NULL, 'V'},
        { "help", 0, NULL, 'h'},
        { "term", 0, NULL, 't'},
        { "out", 1, NULL, 'o'},
        { NULL, 0, NULL, 0},
    };
    if (argc > 2) {
        rule = atoi(argv[1]);
        size = atoi(argv[2]);
    }
    // Comienzo de la validacion de argumentos 
    while ((option = getopt_long(argc, argv, opcionesCortas, opcionesLargas,
            NULL)) != -1) {

        switch (option) {
            case 'h': // -h o --help 
                printHelp(stdout);
                exit(EXIT_SUCCESS);
            case 'V': // -V o --version 
                printVersion(stdout);
                exit(EXIT_SUCCESS);
            case 't': // -t o --terminal
                terminal = SALIDA_TERMINAL;
                estado = PROCESSING;
                break;
            case 'o': // -o , --out
                fileInputName = argv[3];
                // if (optarg == NULL)
                // es una truchada pero no pude hacer andar optarg

                if (argv[5] == NULL || (!strcmp(argv[5], "-t") ||
                        !strcmp(argv[5], "--terminal")))
                    fileOutputName = argv[3];
                else
                    fileOutputName = argv[5];

                //fileOutputName = optarg;
                estado = PROCESSING;
                break;
            default:
                invalidOpt(stderr);
                exit(EXIT_FAILURE);
        }
    }
    if (estado != PROCESSING) {
        printf("la ejecucion es del tipo ./autcel 30 80 input -o \n");
        exit(EXIT_FAILURE);
    }

    // printf("%s-%s-%s-%s-%s-%s-%s \n", argv[0], argv[1], argv[2], argv[3],
          //  argv[4], argv[5], argv[6]);
    fileInput = fopen(fileInputName, "r");
    if (fileInput == NULL) {
        printf("Error en el archivo de entrada\n");
        return EXIT_FAILURE;
    }


    Matrix matrix;
    Matrix_create(&matrix, size);
    printf("Leyendo estado inicial...\n");
    if (loadMatrix(&matrix, fileInput) == 1) {
        fprintf(stderr, "%s", "Archivo de entrada erroneo\n");
        Matrix_destroy(&matrix);
        return INPUT_ERROR;
    }

    Extend(&matrix, rule, terminal);
    printf("Grabando %s\n", fileOutputName);
    fileOutput = fopen(strcat(fileOutputName, ".pbm"), "w+");
    writePbmImage(&matrix, size, fileOutput);
    printf("Listo\n");
    Matrix_destroy(&matrix);
    fclose(fileInput);
    fclose(fileOutput);
    return EXIT_SUCCESS;

}

void writePbmImage(Matrix* matrix, unsigned int n, FILE *file) {
    int width = PIXELWIDTH;
    int height = PIXELHEIGHT;

    fprintf(file, "%s\n", MAGICNUMBER); // Header
    fprintf(file, "%d %d\n", n*PIXELWIDTH, n * PIXELHEIGHT); // Width and Height

    for (int i = 0; i < n; ++i) { // Writing the image
        for (int pixY = 0; pixY < height; ++pixY) {
            for (int j = 0; j < n; ++j) {
                for (int pixX = 0; pixX < width; ++pixX) {
                    unsigned char value = Matrix_read(matrix, i, j);
                    fprintf(file, "%d ", value);
                }
            }
            putc('\n', file);
        }
    }
}

int loadMatrix(Matrix* matrix, FILE* input) {
    for (int j = 0; j < matrix->size; ++j) {
        char c = fgetc(input);
        unsigned char cell = atoi(&c);
        if (cell != 0 && cell != 1) {
            return 1;
        }
        Matrix_write(matrix, cell, 0, j);
    }
    fgetc(input);
    if (fgetc(input) != EOF) {
        return 1;
    }
    return 0;
}

int printHelp(FILE* streamSalida) {
    fprintf(streamSalida, "Uso: \n");
    fprintf(streamSalida, "autcel -h\n");
    fprintf(streamSalida, "autcel -V \n");
    fprintf(streamSalida, "autcel R N inputfile [-o outputprefix[ -t \n");
    fprintf(streamSalida, "Opciones: \n");
    fprintf(streamSalida, "-h, --help	Imprime este mensaje.\n");
    fprintf(streamSalida, "-V, --version    Da la versión del programa.\n");
    fprintf(streamSalida, "-o  Prefijo de los archivos de salida.\n");
    fprintf(streamSalida, "-t, --terminal   Imprime los resultados tambien en consola\n\n");
    fprintf(streamSalida, "Ejemplos:\n");
    fprintf(streamSalida, "autcel 30 80 inicial -o evolucion\n");
    fprintf(streamSalida, "Calcula la evolucion del automata Regla 30\n");
    fprintf(streamSalida, "en un mundo unidimensional de 80 celdas,"
            " por 80 iteraciones.\n");
    fprintf(streamSalida, "El archivo de salida se llamara evolucion.pbm.\n");
    fprintf(streamSalida, "Si no se da un prefijo para los archivos de "
            "salida,\n");
    fprintf(streamSalida, "el prefijo será el nombre del archivo de entrada.\n");
    fprintf(streamSalida, "autcel 30 80 inicial -o evolucion -t\n");
    fprintf(streamSalida, "para imprimir tambien por pantalla la evolucion.\n");

    return EXIT_SUCCESS;
}

int printVersion(FILE* streamSalida) {
    fprintf(streamSalida, "TP1: v1.0.\n");
    return EXIT_SUCCESS;
}

int validar(FILE* streamSalida, int argc, char** argv) {
    int codReturn = PROCESSING;
    if (argc < 5) {
        fprintf(streamSalida, "TP1: error en la cantidad de argumentos \n");
        codReturn = ERR_CANT_ARGS;
    }
    return codReturn;
}

int invalidOpt(FILE* streamSalida) {
    fprintf(streamSalida, "TP1: Opción invalida \n");
    return INVALID_OPTION;
}
