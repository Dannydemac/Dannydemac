#include <stdio.h>
#include <stdlib.h>
#include "circular_list.h"

static void display_circular_list(const CircularList *list) {
    CircularNode *current;
    float *value;
    int index = 0;

    printf("Tamaño de la lista circular: %d\n", circular_list_size(list));

    current = circular_list_head(list);
    printf("\n");
    for (index = 0; index < circular_list_size(list); index++) {
        value = (float *)circular_list_data(current);
        printf("circular.node[%03d]=%.2f, %p -> %p\n", index, *value, current, circular_list_next(current));
        current = circular_list_next(current);
    }
}

void insert_after_first(CircularList *list, float value) {
    float *new_data = (float *)malloc(sizeof(float));
    if (new_data == NULL) {
        perror("Error en la asignación de memoria");
        exit(EXIT_FAILURE);
    }
    *new_data = value;
    circular_list_insert_next(list, circular_list_head(list), new_data);
}

void insert_at_start(CircularList *list, float value) {
    float *new_data = (float *)malloc(sizeof(float));
    if (new_data == NULL) {
        perror("Error en la asignación de memoria");
        exit(EXIT_FAILURE);
    }
    *new_data = value;
    circular_list_insert_next(list, NULL, new_data); 
}

void insert_at_end(CircularList *list, float value) {
    CircularNode *last_node = circular_list_head(list);
    while (circular_list_next(last_node) != circular_list_head(list)) {
        last_node = circular_list_next(last_node);
    }
    float *new_data = (float *)malloc(sizeof(float));
    if (new_data == NULL) {
        perror("Error en la asignación de memoria");
        exit(EXIT_FAILURE);
    }
    *new_data = value;
    circular_list_insert_next(list, last_node, new_data);
}

void insert_after_third(CircularList *list, float value) {
    CircularNode *third_node = circular_list_head(list);
    for (int i = 0; i < 2; i++) {
        third_node = circular_list_next(third_node);
    }
    float *new_data = (float *)malloc(sizeof(float));
    if (new_data == NULL) {
        perror("Error en la asignación de memoria");
        exit(EXIT_FAILURE);
    }
    *new_data = value;
    circular_list_insert_next(list, third_node, new_data);
}

void delete_head(CircularList *list) {
    float *data;
    circular_list_remove_next(list, NULL, (void **)&data);
    free(data);
}

void delete_after_head(CircularList *list) {
    float *data;
    circular_list_remove_next(list, circular_list_head(list), (void **)&data);
    free(data);
}

void delete_last(CircularList *list) {
    CircularNode *current = circular_list_head(list);
    while (circular_list_next(circular_list_next(current)) != circular_list_head(list)) {
        current = circular_list_next(current);
    }
    float *data;
    circular_list_remove_next(list, current, (void **)&data);
    free(data);
}

void delete_third(CircularList *list) {
    CircularNode *second_node = circular_list_head(list);
    for (int i = 0; i < 1; i++) {
        second_node = circular_list_next(second_node);
    }
    float *data;
    circular_list_remove_next(list, second_node, (void **)&data);
    free(data);
}

int main() {
    CircularList myList;
    int i;

    circular_list_init(&myList, free);

    for (i = 0; i < 10; i++) {
        float *value = (float *)malloc(sizeof(float));
        if (value == NULL) return EXIT_FAILURE;
        *value = i + 0.5f;
        if (circular_list_insert_next(&myList, NULL, value) != 0) return EXIT_FAILURE;
    }

    display_circular_list(&myList);

    insert_at_start(&myList, 125.32f);
    insert_after_first(&myList, 8.48f);
    insert_at_end(&myList, 9.27f);
    insert_after_third(&myList, 12.36f);

    printf("\nInsertando elementos...\n");
    display_circular_list(&myList);

    delete_head(&myList);
    delete_after_head(&myList);
    delete_last(&myList);
    delete_third(&myList);

    printf("\nEliminando elementos...\n");
    display_circular_list(&myList);

    circular_list_destroy(&myList);
    printf("\nLista destruida.\n");

    return 0;
}

