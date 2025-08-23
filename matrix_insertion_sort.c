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


// Intercambia las columnas c1 y c2 de la fila "row" hacia abajo
void swap_columns(int **matrix, int row, int c1, int c2, int n) {
    for (int k = row; k < n; k++) { //Desde el i-ésimo renglón hasta el final de la matriz
        int temp = matrix[k][c1]; //Intercambiamos los elementos de las columnas c1 y c2, para cada k desde i hasta n-1
        matrix[k][c1] = matrix[k][c2];
        matrix[k][c2] = temp;
    }
}

// Se aplica quicksort a cada renglón de la matriz enviado desde sort_matrix
void quicksort_row(int **matrix, int row, int left, int right, int n) {
    int pivot = matrix[row][(left + right) / 2]; //El pivote es el elemento del renglon i con índice medio
    int l = left, r = right; //Necesitamos una copia de left y right para no perder su valor original, pues l y r se van a modificar

    while (l <= r) {
        while (matrix[row][l] < pivot) l++; //Buscamos el primer elemento mayor o igual al pivote
        while (matrix[row][r] > pivot) r--; //BUscamos el ultimo elemento menor o igual al pivote

        if (l <= r) { //Si l es menor o igual a r, significa que hay elementos fuera de lugar
            swap_columns(matrix, row, l, r, n); //Llamamos a la función que intercambia las columnas l y r desde el renglon i hacia abajo
            l++; //Avanzamos l y retrocedemos r para seguir buscando elementos fuera de lugar
            r--;
        }
    }

    if (left < r) quicksort_row(matrix, row, left, r, n); //Si al terminar el ciclo while, left es menor que r, significa que hay elementos a la izquierda del pivote que deben ordenarse, por lo tanto mandamos solo esa sección a ordenarse
    if (l < right) quicksort_row(matrix, row, l, right, n); //Si al terminar el ciclo while, l es menor que right, significa que hay elementos a la derecha del pivote que deben ordenarse
}

void sort_matrix(int **matrix, int n) {
    for (int i = 0; i < n; i++) {
        quicksort_row(matrix, i, 0, n - 1, n); //Manda ordenar cada i renglón
    }
}

int main() {
    int n = 3;
    // Reserva dinámica de la matriz
    int **matrix = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        matrix[i] = (int *)malloc(n * sizeof(int));
    }

    // Ejemplo de entrada
    int ejemplo[3][3] = {
        {4, 7, 2},
        {9, 5, 6},
        {8, 1, 3}
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