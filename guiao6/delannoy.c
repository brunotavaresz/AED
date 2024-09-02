#include <stdio.h>

int delannoy(int m, int n) {

    if (m == 0 || n == 0) {
        return 1;
    }
    

    return delannoy(m - 1, n) + delannoy(m - 1, n - 1) + delannoy(m, n - 1);
}

int main() {
    int m, n;
    printf("Informe os valores de m e n: ");
    scanf("%d %d", &m, &n);
    
    int resultado = delannoy(m, n);
    
    printf("O número de Delannoy D(%d, %d) é %d\n", m, n, resultado);


    
    return 0;
}
