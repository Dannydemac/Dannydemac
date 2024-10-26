#include <stdio.h>
#include <stdlib.h>
#include "dlist.h"

static void mostrar_lista(const DList *lista) {
    DListNode *nodo;
    char *info;
    int contador = 0;

    printf("El tamaño de la lista es: %d\n", dlist_size(lista));

    nodo = dlist_head(lista);
    while (nodo != NULL) {
        info = (char *)dlist_data(nodo);
        printf("lista.nodo[%02d] = %c, %p <- %p -> %p\n", contador, *info, nodo->prev, nodo, nodo->next);
        contador++;
        nodo = dlist_next(nodo);
    }

    return;
}

int main(int argc, char **argv) {
    DList lista;
    DListNode *nodo_actual;
    char *info;
    int indice;

    dlist_init(&lista, free);

    char iniciales[10] = {'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T'};

    for (indice = 0; indice < 10; indice++) {
        if ((info = (char *)malloc(sizeof(char))) == NULL)
            return 1;

        *info = iniciales[indice];

        if (dlist_ins_next(&lista, dlist_tail(&lista), info) != 0)
            return 1;
    }

    mostrar_lista(&lista);

    nodo_actual = dlist_head(&lista);
    for (indice = 0; indice < 6; indice++) {
        nodo_actual = dlist_next(nodo_actual);
    }

    info = (char *)dlist_data(nodo_actual);
    printf("\nEliminando el nodo con valor: %c\n", *info);

    if (dlist_remove(&lista, nodo_actual, (void **)&info) != 0)
        return 1;

    mostrar_lista(&lista);

    printf("\nAgregando 'U' al final de la lista\n");
    if ((info = (char *)malloc(sizeof(char))) == NULL)
        return 1;

    *info = 'U';
    if (dlist_ins_next(&lista, dlist_tail(&lista), info) != 0)
        return 1;

    mostrar_lista(&lista);

    printf("\nEliminando el segundo nodo\n");
    if (dlist_remove(&lista, dlist_next(dlist_head(&lista)), (void **)&info) != 0)
        return 1;

    mostrar_lista(&lista);

    printf("\nEliminando la cabeza de la lista\n");
    if (dlist_remove(&lista, dlist_head(&lista), (void **)&info) != 0)
        return 1;

    mostrar_lista(&lista);

    printf("\nInsertando 'V' en la cabeza de la lista\n");
    if ((info = (char *)malloc(sizeof(char))) == NULL)
        return 1;

    *info = 'V';
    if (dlist_ins_prev(&lista, dlist_head(&lista), info) != 0)
        return 1;

    mostrar_lista(&lista);

    printf("\nEliminando el nodo en la posición 4\n");
    nodo_actual = dlist_head(&lista);
    for (indice = 0; indice < 4; indice++) {
        nodo_actual = dlist_next(nodo_actual);
    }

    if (dlist_remove(&lista, nodo_actual, (void **)&info) != 0)
        return 1;

    mostrar_lista(&lista);

    printf("\nInsertando 'W' después del primer nodo\n");
    if ((info = (char *)malloc(sizeof(char))) == NULL)
        return 1;

    *info = 'W';
    if (dlist_ins_next(&lista, dlist_head(&lista), info) != 0)
        return 1;

    mostrar_lista(&lista);

    printf("\nDestruyendo la lista...\n");
    dlist_destroy(&lista);

    return 0;
}

