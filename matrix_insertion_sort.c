#include <stdio.h>
#include <stdlib.h>

/*
 * EJERCICIO:
 * Se quiere definir un programa que, dada una matriz cuadrada con valores enteros,
 * devuelva una permutación de los valores de modo que:
 *
 * 1. Cada renglón esté ordenado de menor a mayor.
 * 2. Todos los elementos del segundo renglón (de arriba hacia abajo)
 *    sean mayores que los del primero, los del tercero mayores que los del segundo, etc.
 *
 * Regla importante:
 * - Cuando se ordenan los elementos de un renglón, por cada elemento de dicho renglón,
 *   se mueven también todos los elementos que se encuentran por debajo en la misma columna.
 *
 * INSTRUCCIONES:
 * - Completa la función sort_matrix() que debe modificar la matriz en su lugar.
 * - Puedes escribir funciones auxiliares si lo deseas.
 * - NO cambies la firma de sort_matrix().
 */

void sort_matrix(int **matrix, int n) {
    // TODO: Implementa aquí el algoritmo.
    // Necesitarás el método de inserción,
    // pero recuerda aplicar la regla de mover toda la columna.
    int sorted = 1;
    do{
        sorted = 1;
        for(int i = 0; i<n; i++){ //renglones
            for(int j = 0; j<n-1; j++){ //columnas
                if(matrix[i][j] > matrix[i][j+1]){ //Si el elemento de i,j es mayor que el que tiene a su derecha, los intercambia
                    sorted = 0;
                    int temp = matrix[i][j];
                    matrix[i][j] = matrix[i][j+1];
                    matrix[i][j+1] = temp;
                    for(int k=i+1; k<n; k++){ //Como se cambiaron los elementos de i, j e i, j+1, se tienen que intercambiar todos los que tienen por debajo. k es i+1 porque es el elemento que está directamente abajo del elemento original intercambiado, y se hará para todos los que estén debajo.
                        int temp = matrix[k][j];
                        matrix[k][j] = matrix[k][j+1];
                        matrix[k][j+1] = temp;
                    }
                }
            }
        }
        //El do while se usa pues se intercambia por pares solamente, por lo tanto, hasta que la matriz esté totalmente ordenada (cada elemento i,j es menor o igual a i, j+1) se sale del ciclo.
    }while(!sorted);

    //Si bien sé que se puede optimizar, esta es la solución brute force que hice con el poco tiempo que tuve.
}

int main() {
    int n = 4;
    // Reserva dinámica de la matriz
    int **matrix = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        matrix[i] = (int *)malloc(n * sizeof(int));
    }

    // Ejemplo de entrada
    int ejemplo[4][4] = {
        {9, 2, 7, 5},
        {4, 6, 3, 0},
        {5, 1, 8, 7},
        {9, 1, 8, 5}
    };

    // Copiar ejemplo a la matriz dinámica
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = ejemplo[i][j];
        }
    }

    printf("Matriz original:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    // Llamada a la función que deben completar
    sort_matrix(matrix, n);

    printf("\nMatriz ordenada:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    // Liberar memoria
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}