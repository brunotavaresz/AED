#include <stdio.h>

int count_elements_with_property(int array[], int n) {
    int count = 0;
    
    for (int i = 1; i < n - 1; i++) {
        if (array[i] == array[i - 1] + array[i + 1]) {
            count++;
        }
    }
    
    return count;
}

int main() {
    int array1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int n1 = sizeof(array1) / sizeof(array1[0]); 
    
    int array2[] = {1, 2, 1, 4, 5, 6, 7, 8, 9, 10};
    int n2 = sizeof(array2) / sizeof(array2[0]); 
    
    int array3[] = {1, 2, 1, 3, 2, 6, 7, 8, 9, 10};
    int n3 = sizeof(array3) / sizeof(array3[0]); 
    
    int array4[] = {0, 2, 2, 0, 3, 3, 0, 4, 4, 0};
    int n4 = sizeof(array4) / sizeof(array4[0]); 
    
    int array5[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int n5 = sizeof(array5) / sizeof(array5[0]);  
    
    printf("Elementos que obedecem à condição (sequência 1): %d\n", count_elements_with_property(array1, n1));
    printf("Elementos que obedecem à condição (sequência 2): %d\n", count_elements_with_property(array2, n2));
    printf("Elementos que obedecem à condição (sequência 3): %d\n", count_elements_with_property(array3, n3));
    printf("Elementos que obedecem à condição (sequência 4): %d\n", count_elements_with_property(array4, n4));
    printf("Elementos que obedecem à condição (sequência 5): %d\n", count_elements_with_property(array5, n5));
    
    return 0;
}


// Nº de operações desempenho do algoritmo é linear, o que significa que o número de operações aumenta proporcionalmente ao tamanho da entrada.
// À medida que o tamanho da entrada (n) aumenta, o número de comparações também aumenta linearmente.