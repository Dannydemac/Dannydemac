#include <stdio.h>
#include <stdlib.h>
#include "double_circular_list.h"

// Función para crear un nuevo nodo
Node* nuevo_nodo(int valor) {
    Node* nodo = (Node*)malloc(sizeof(Node));
    if (!nodo) {
        printf("Error: no se pudo asignar memoria para el nodo\n");
        return NULL;
    }

    nodo->valor = valor;
    nodo->siguiente = NULL;
    nodo->anterior = NULL;

    return nodo;
}

void agregar_al_final(Node** cabeza, int valor) {
    Node* nodo_nuevo = nuevo_nodo(valor);
    if (!nodo_nuevo) return;

    if (*cabeza == NULL) {
        *cabeza = nodo_nuevo;
        nodo_nuevo->siguiente = nodo_nuevo;
        nodo_nuevo->anterior = nodo_nuevo;
    } else {
        Node* ultimo = (*cabeza)->anterior;
        ultimo->siguiente = nodo_nuevo;
        nodo_nuevo->anterior = ultimo;
        nodo_nuevo->siguiente = *cabeza;
        (*cabeza)->anterior = nodo_nuevo;
    }
}

void mostrar_lista(Node* cabeza) {
    if (cabeza == NULL) {
        printf("La lista está vacía.\n");
        return;
    }

    Node* actual = cabeza;
    printf("Contenido de la lista circular doblemente enlazada:\n");
    do {
        printf("Nodo: %p | Valor: %d | Siguiente: %p | Anterior: %p\n", 
               (void*)actual, actual->valor, (void*)actual->siguiente, (void*)actual->anterior);
        actual = actual->siguiente;
    } while (actual != cabeza);

    printf("\n");
}

void liberar_lista(Node** cabeza) {
    if (*cabeza == NULL) return;

    Node* actual = *cabeza;
    Node* siguiente_nodo;

    do {
        siguiente_nodo = actual->siguiente;
        free(actual);
        actual = siguiente_nodo;
    } while (actual != *cabeza);

    *cabeza = NULL;
}

