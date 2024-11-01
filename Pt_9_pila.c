#include <stdio.h>
#include <stdlib.h>
#include "pila.h"

static void mostrar_pila(const Pila *pila) {
    NodoLista *nodo;
    double *valor;
    int i = 0;
    printf("El tamaño de la pila es %d\n\n", pila_tamano(pila));

    nodo = pila_inicio(pila);
    while (nodo != NULL) {
        valor = (double *)obtener_dato(nodo);
        printf("pila.nodo[%03d]=%03f, %p -> %p \n", i, *valor, nodo, nodo->siguiente);
        i++;
        nodo = obtener_siguiente(nodo);
    }
    printf("\n");
}

void inicializar_pila(Pila *pila) {
    for (int i = 1; i <= 10; i++) {
        double *valor = (double *)malloc(sizeof(double));
        if (valor != NULL) {
            *valor = i * 10.0;
            apilar(pila, valor);
        }
    }
}

void agregar_elementos(Pila *pila) {
    for (int i = 1; i <= 4; i++) {
        double *valor = (double *)malloc(sizeof(double));
        if (valor != NULL) {
            *valor = i * 100.0;
            apilar(pila, valor);
            printf("Insertando %f...\n", *valor);
            mostrar_pila(pila);
        }
    }
}

void quitar_elementos(Pila *pila) {
    for (int i = 0; i < 2; i++) {
        double *valor;
        if (desapilar(pila, (void **)&valor) == 0) {
            printf("Eliminando %f...\n", *valor);
            free(valor);
            mostrar_pila(pila);
        } else {
            fprintf(stderr, "No se pudo eliminar el elemento (pila vacía)\n");
        }
    }
}

int main(int argc, char **argv) {
    Pila pila;
    inicializar_pila(&pila);
    mostrar_pila(&pila);
    agregar_elementos(&pila);
    quitar_elementos(&pila);
    printf("Destruyendo la pila...\n");
    destruir_pila(&pila);
    return 0;
}

