//Godinez Esacreño Leonardo Daniel

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int n, i;
    printf("Cantidad de alumnos: ");
    scanf("%d", &n);
    getchar();

    char alumnos[n][3][25];

    for (i = 0; i < n; i++) {
        printf("Ingrese el nombre del alumno %d (máximo 25 caracteres): ", i + 1);
        fgets(alumnos[i][0], 25, stdin);
        alumnos[i][0][strcspn(alumnos[i][0], "\n")] = '\0';
        
        printf("Ingrese la edad del alumno %d: ", i + 1);
        int edad;
        scanf("%d", &edad);
        sprintf(alumnos[i][1], "%d", edad);

        printf("Ingrese la calificación del alumno %d: ", i + 1);
        int calificacion;
        scanf("%d", &calificacion);
        sprintf(alumnos[i][2], "%d", calificacion);
        
        getchar();
    }

    int suma_edades = 0, suma_calificaciones = 0;
    for (i = 0; i < n; i++) {
        suma_edades += atoi(alumnos[i][1]);
        suma_calificaciones += atoi(alumnos[i][2]);
    }
    float promedio_edad = (float)suma_edades / n;
    float promedio_calificacion = (float)suma_calificaciones / n;

    printf("\nPromedio de edad: %.2f\n", promedio_edad);
    printf("Promedio de calificación: %.2f\n", promedio_calificacion);

    printf("\nNombres de los alumnos en orden inverso:\n");
    for (i = n - 1; i >= 0; i--) {
        printf("%s\n", alumnos[i][0]);
    }

    return 0;
}

