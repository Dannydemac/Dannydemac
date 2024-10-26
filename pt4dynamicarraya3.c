//GodineZ Escareño Leonardo Daniel

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char numero_cuenta[10];
    int i, j, k, tam, num;

    printf("Ingrese su número de cuenta: ");
    scanf("%19s", numero_cuenta);

    tam = strlen(numero_cuenta);

    int **matriz = (int **)malloc(tam * sizeof(int *));
    if (matriz == NULL) {
        printf("Error al asignar memoria para las filas.\n");
        return -1;
    }

    for (i = 0; i < tam; i++) {
        num = numero_cuenta[i] - '0';
        if (num == 0) {
            matriz[i] = NULL;
        } else {
            matriz[i] = (int *)malloc(num * sizeof(int));
            if (matriz[i] == NULL) {
                printf("Error al asignar memoria para la fila %d.\n", i);
                for (k = 0; k < i; k++) {
                    if (matriz[k] != NULL) {
                        free(matriz[k]);
                    }
                }
                free(matriz);
                return -1;
            }
            for (j = 0; j < num; j++) {
                matriz[i][j] = num;
            }
        }
    }

    printf("\nMatriz generada:\n");
    for (i = 0; i < tam; i++) {
        if (matriz[i] == NULL) {
            printf("|NULL|\n");
        } else {
            for (j = 0; j < (numero_cuenta[i] - '0'); j++) {
                printf(" %d |", matriz[i][j]);
            }
            printf("\n");
        }
    }

    for (i = 0; i < tam; i++) {
        if (matriz[i] != NULL) {
            free(matriz[i]);
        }
    }
    free(matriz);

    return 0;
}
