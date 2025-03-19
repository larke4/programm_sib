#include <stdio.h>

float deter(float matrix[3][3], int n) {
    float det = 0;
    if (n == 2) {
        det = matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
    } else if (n == 3) {
        det = matrix[0][0] * (matrix[1][1] * matrix[2][2] - matrix[1][2] * matrix[2][1]) -
              matrix[0][1] * (matrix[1][0] * matrix[2][2] - matrix[1][2] * matrix[2][0]) +
              matrix[0][2] * (matrix[1][0] * matrix[2][1] - matrix[1][1] * matrix[2][0]);
    }
    return det;
}
int main() {
    int n;

    printf("razmer matrix n: ");
    scanf("%d", &n);

    if (n != 2 && n != 3) {
        printf("razmer doljen bit 2 or 3");
        return 1;
    }

    float A[3][3], B[3];

    printf("Vvedite koff matrix:"); //забиваем матрицу коэфицентов
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%f", &A[i][j]);
        }
    }

    printf("Vvedite koff free matrix:"); // забиваем разширенную матрицу
    for (int i = 0; i < n; i++) {
        scanf("%f", &B[i]);
    }

    float det_A = deter(A, n);
    
    if (det_A == 0) {
        printf("sistema ne imeet rehenii");
    }
    // решение системы уравнений Cлау по крамеру заменя i столбец на 
    float X[3];
    for (int i = 0; i < n; i++) {
        float Ai[3][3];
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                Ai[j][k] = A[j][k];
            }
        }
        for (int j = 0; j < n; j++) {
            Ai[j][i] = B[j]; // Заменяем i-тый столбец на B
        }
        
        X[i] = deter(Ai, n) / det_A; // Находим переменную X[i]
    }

    printf("rehenie sistem: ");
    for (int i = 0; i < n; i++) {
        printf("x[%d] = %.2f ", i + 1, X[i]);
    }
}
