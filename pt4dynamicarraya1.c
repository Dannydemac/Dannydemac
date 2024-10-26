//Godinez Escareño Leonardo Daniel

#include <stdio.h>
#include <stdlib.h>

int main() {
    int i, j, cuenta;
    int num[10];


    for (i = 0; i < 10; i++) {
        num[i] = (i + 1) * 2;
    }

    printf("Lista de pares en orden inverso:\n\n");
    for (i = 9; i >= 0; i--) {
        printf(" %d |", num[i]);
    }
    
    printf("\n\nNúmero de cuenta: ");
    scanf("%d", &cuenta);
    
    j = cuenta % 10;
    if (j >= 0 && j < 10) {
        num[j] = -1;
    }
    
    printf("\nLista con -1 en el índice correspondiente:\n\n");
    for (i = 0; i < 10; i++) {
        printf(" %d |", num[i]);
    }

    return 0;
}


