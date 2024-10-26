#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

void insert_at_head(List *list, char data) {
    char *new_data = (char *)malloc(sizeof(char));
    *new_data = data;
    if (list_ins_next(list, NULL, new_data) != 0) {
        printf("Error al insertar en la cabeza.\n");
    }
}

void insert_at_tail(List *list, char data) {
    char *new_data = (char *)malloc(sizeof(char));
    *new_data = data;
    if (list_ins_next(list, list_tail(list), new_data) != 0) {
        printf("Error al insertar en la cola.\n");
    }
}

void insert_after(List *list, ListNode *node, char data) {
    char *new_data = (char *)malloc(sizeof(char));
    *new_data = data;
    if (list_ins_next(list, node, new_data) != 0) {
        printf("Error al insertar después del nodo.\n");
    }
}

void remove_from_head(List *list) {
    char *data;
    if (list_rem_next(list, NULL, (void **)&data) == 0) {
        free(data);
    } else {
        printf("Error al eliminar de la cabeza.\n");
    }
}

void remove_after(List *list, ListNode *node) {
    char *data;
    if (list_rem_next(list, node, (void **)&data) == 0) {
        free(data);
    } else {
        printf("Error al eliminar después del nodo.\n");
    }
}

static void print_list(const List *list) {
    ListNode *node = list_head(list);
    int i = 0;

    printf("Contenido de la lista:\n");
    while (node != NULL) {
        printf("Elemento[%03d]: %c\n", i, *(char *)list_data(node));
        node = list_next(node);
        i++;
    }
    printf("Tamaño de la lista: %d\n", list_size(list));
}

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Uso: %s <caracteres separados por espacio>\n", argv[0]);
        return 1;
    }

    List list;
    list_init(&list, free);

    for (int i = 1; i < argc; i++) {
        char *data = (char *)malloc(sizeof(char));
        *data = argv[i][0];
        if (list_ins_next(&list, list_tail(&list), data) != 0) {
            printf("Error al insertar elemento.\n");
            return 1;
        }
    }

    print_list(&list);

    insert_at_head(&list, 'D');
    insert_at_tail(&list, 'R');
    insert_after(&list, list_head(&list), 'o');
    insert_after(&list, list_tail(&list), '9');

    printf("\nLista después de las inserciones adicionales:\n");
    print_list(&list);

    remove_from_head(&list);
    remove_after(&list, list_head(&list));
    remove_after(&list, list_tail(&list));

    printf("\nLista después de las eliminaciones:\n");
    print_list(&list);

    list_destroy(&list);

    return 0;
}

