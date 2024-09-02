#include <stdio.h>
#include <assert.h>

int contarTernos(int array[], int n) {
    assert(n>2);
    int count = 0; 
    int comparisons = 0; 

    for (int k = 2; k < n; k++) {
        for (int j = 1; j < k; j++) {
            for (int i = 0; i < j; i++) {
                comparisons++;
                if (array[k] == array[i] + array[j]) {
                    count++;
                }
            }
        }
    }

    printf("Número de comparações efetuadas: %d\n", comparisons);

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

    int array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
               11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
               21, 22, 23, 24, 25, 26, 27, 28, 29, 30,
               31, 32, 33, 34, 35, 36, 37, 38, 39, 40}; // Exemplo de uma sequência de 5 elementos.
    int n = sizeof(array) / sizeof(array[0]);

    int ternos = contarTernos(array, n);
    printf("Número de ternos que satisfazem a propriedade: %d\n", contarTernos(array, n));
    printf("Número de ternos que satisfazem a propriedade: %d\n", contarTernos(array1, n1));
    printf("Número de ternos que satisfazem a propriedade: %d\n", contarTernos(array2, n2));
    printf("Número de ternos que satisfazem a propriedade: %d\n", contarTernos(array3, n3));
    printf("Número de ternos que satisfazem a propriedade: %d\n", contarTernos(array4, n4));
    printf("Número de ternos que satisfazem a propriedade: %d\n", contarTernos(array5, n5));

    

    return 0;
}
