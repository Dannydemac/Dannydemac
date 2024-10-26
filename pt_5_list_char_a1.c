#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

static void print_list(const List *list) {
    ListNode *node;
    char *data;
    int i;

    fprintf(stdout, "List size is %d\n", list_size(list));

    i = 0;
    node = list_head(list);

    while (1) {
        data = list_data(node);
        fprintf(stdout, "list.node[%03d]=%c, %p -> %p \n", i, *data, node, node->next);

        i++;

        if (list_is_tail(node))
            break;
        else
            node = list_next(node);
    }

    return;
}

void add_head(List *list, char value) {
    char *data = (char *)malloc(sizeof(char));
    *data = value;
    list_ins_next(list, NULL, data);
}

void add_tail(List *list, char value) {
    char *data = (char *)malloc(sizeof(char));
    *data = value;
    list_ins_next(list, list_tail(list), data);
}

void add_after(List *list, ListNode *node, char value) {
    char *data = (char *)malloc(sizeof(char));
    *data = value;
    list_ins_next(list, node, data);
}

void add_before(List *list, ListNode *node, char value) {
    ListNode *prev = NULL;
    ListNode *current = list_head(list);
    
    while (current != NULL && current != node) {
        prev = current;
        current = list_next(current);
    }

    if (current == node) {
        char *data = (char *)malloc(sizeof(char));
        *data = value;
        list_ins_next(list, prev, data);
    }
}

void remove_head(List *list) {
    char *data;
    list_rem_next(list, NULL, (void **)&data);
    free(data);
}

void remove_tail(List *list) {
    ListNode *node = list_head(list);
    ListNode *prev = NULL;

    while (!list_is_tail(node)) {
        prev = node;
        node = list_next(node);
    }

    char *data;
    list_rem_next(list, prev, (void **)&data);
    free(data);
}

void remove_after(List *list, ListNode *node) {
    char *data;
    list_rem_next(list, node, (void **)&data);
    free(data);
}

void remove_at(List *list, int position) {
    ListNode *node = list_head(list);
    ListNode *prev = NULL;

    for (int i = 0; i < position && node != NULL; i++) {
        prev = node;
        node = list_next(node);
    }

    if (node != NULL) {
        char *data;
        list_rem_next(list, prev, (void **)&data);
        free(data);
    }
}

int main() {
    List list;
    ListNode *node;
    char *data;
    int i;

    list_init(&list, free);

    char initial_chars[10] = {'X', 'Y', 'Z', 'L', 'M', 'N', 'O', 'P', 'Q', 'R'};
    for (i = 0; i < 10; i++) {
        data = (char *)malloc(sizeof(char));
        *data = initial_chars[i];
        list_ins_next(&list, NULL, data);
    }

    print_list(&list);

    printf("\nAdding 'A' at the head\n");
    add_head(&list, 'A');
    print_list(&list);

    printf("\nAdding 'W' at the tail\n");
    add_tail(&list, 'W');
    print_list(&list);

    printf("\nAdding 'T' after the second node\n");
    node = list_head(&list);
    node = list_next(node);
    add_after(&list, node, 'T');
    print_list(&list);

    printf("\nAdding 'M' before the fourth node\n");
    node = list_head(&list);
    for (i = 0; i < 3; i++) {
        node = list_next(node);
    }
    add_before(&list, node, 'M');
    print_list(&list);

    printf("\nRemoving the head\n");
    remove_head(&list);
    print_list(&list);

    printf("\nRemoving the tail\n");
    remove_tail(&list);
    print_list(&list);

    printf("\nRemoving the node after the first\n");
    node = list_head(&list);
    remove_after(&list, node);
    print_list(&list);

    printf("\nRemoving the third node\n");
    remove_at(&list, 2);
    print_list(&list);

    printf("\nDestroying the list\n");
    list_destroy(&list);

    return 0;
}

