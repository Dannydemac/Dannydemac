#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char *palindromo;
    int posicion;
} Palindromo;

char* leerArchivo(const char *nombreArchivo);
int esPalindromo(const char *palabra);
Palindromo* buscarPalindromos(const char *texto, int *cantidadPalindromos);
void liberarPalindromos(Palindromo *palindromos, int cantidad);

int main() {
	int i;
    const char *nombreArchivo = "file.txt";
    int cantidadPalindromos = 0;

    char *texto = leerArchivo(nombreArchivo);
    if (texto == NULL) {
        fprintf(stderr, "Error al leer el archivo\n");
        return 1;
    }

    Palindromo *palindromos = buscarPalindromos(texto, &cantidadPalindromos);

    printf("Palíndromos encontrados: %d\n", cantidadPalindromos);
    for (i = 0; i < cantidadPalindromos; i++) {
        printf("Palíndromo: '%s' en posición %d\n", palindromos[i].palindromo, palindromos[i].posicion);
    }

    liberarPalindromos(palindromos, cantidadPalindromos);
    free(texto);

    return 0;
}

char* leerArchivo(const char *nombreArchivo) {
    FILE *archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL) {
        return NULL;
    }

    fseek(archivo, 0, SEEK_END);
    long tamano = ftell(archivo);
    rewind(archivo);

    char *contenido = (char*)malloc((tamano + 1) * sizeof(char));
    if (contenido == NULL) {
        fclose(archivo);
        return NULL;
    }

    fread(contenido, sizeof(char), tamano, archivo);
    contenido[tamano] = '\0';
    fclose(archivo);

    return contenido;
}

int esPalindromo(const char *palabra) {
	int i;
    int len = strlen(palabra);
    for (i = 0; i < len / 2; i++) {
        if (tolower(palabra[i]) != tolower(palabra[len - 1 - i])) {
            return 0;
        }
    }
    return 1;
}

Palindromo* buscarPalindromos(const char *texto, int *cantidadPalindromos) {
    Palindromo *palindromos = NULL;
    char palabra[100];
    int posicion = 0, palabraInicio = 0;

    while (sscanf(texto + palabraInicio, "%s%n", palabra, &posicion) == 1) {
        if (esPalindromo(palabra)) {
            palindromos = realloc(palindromos, (*cantidadPalindromos + 1) * sizeof(Palindromo));
            palindromos[*cantidadPalindromos].palindromo = strdup(palabra);
            palindromos[*cantidadPalindromos].posicion = palabraInicio;
            (*cantidadPalindromos)++;
        }
        palabraInicio += posicion;
    }

    return palindromos;
}

void liberarPalindromos(Palindromo *palindromos, int cantidad) {
	int i;
    for (i = 0; i < cantidad; i++) {
        free(palindromos[i].palindromo);
    }
    free(palindromos);
}

