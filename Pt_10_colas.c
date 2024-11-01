#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mi_cola.h"
#include "mi_lista.h"

int contador;

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Uso correcto: %s <lista de palabras>\n", argv[0]);
        return 1;
    }

    Cola mi_cola;
    inicializar_cola(&mi_cola, free);

    for (contador = 1; contador < argc; contador++) {
        char *texto = strdup(argv[contador]);
        if (encolar(&mi_cola, texto) != 0) {
            printf("Error al intentar encolar\n");
            destruir_cola(&mi_cola);
            return 1;
        }
    }

    printf("La cola contiene %d elementos\n", tamano_cola(&mi_cola));

    char *texto_desencolado;
    while (tamano_cola(&mi_cola) > 0) {
        if (desencolar(&mi_cola, (void **)&texto_desencolado) == 0) {
            printf("Elemento desencolado: %s\n", texto_desencolado);
            free(texto_desencolado);
        }
    }

    destruir_cola(&mi_cola);

    return 0;
}

