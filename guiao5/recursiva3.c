#include <stdio.h>

int recursiveFunction3(int n, int *count) {
    (*count)++;  // Contador de chamadas recursivas
    if (n <= 1) {
        return 1;
    }
    if (n % 2 == 0) {
        int m = n / 2;
        return 2 * recursiveFunction3(m, count) + n;
    } else {
        int m1 = n / 2;
        int m2 = (n + 1) / 2;
        return recursiveFunction3(m1, count) + recursiveFunction3(m2, count) + n;
    }
}

int main() {
    int n = 10; // Substitua pelo valor desejado
    int count = 0; // Inicializa o contador
    int result = recursiveFunction3(n, &count);
    printf("Resultado: %d\n", result);
    printf("Número de chamadas recursivas: %d\n", count);
    return 0;
}
