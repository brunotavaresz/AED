// Display the contents of array a with n elements
// Pre-Conditions: a != NULL and n > 0
// Example of produced output: Array = [ 1.00, 2.00, 3.00 ]

#include <stdio.h>
#include <stddef.h> // Para size_t

void DisplayArray(double* a, size_t n) {
    if (a == NULL || n == 0) {
        printf("Pré-condições não atendidas. A função requer um array não nulo e n > 0.\n");
        return;
    }
    
    printf("Array = [ ");
    
    for (size_t i = 0; i < n; i++) {
        printf("%.2lf", a[i]); // duas casas decimais
        if (i < n - 1) {
            printf(", "); // Adiciona uma vírgula e um espaço após todos os elementos, exceto o último
        }
    }
    
    printf(" ]\n"); // Fecha o array e imprime uma nova linha
}

int main() {
    double myArray[] = {1.0, 2.0, 3.0, 4.0, 5.0};
    size_t n = sizeof(myArray) / sizeof(myArray[0]);
    
    DisplayArray(myArray, n);
    
    return 0;
}
