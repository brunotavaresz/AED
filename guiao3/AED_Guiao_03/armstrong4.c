#include <stdio.h>
#include <math.h>

int calcularPotencia(int base, int expoente) {
    int resultado = 1;
    for (int i = 0; i < expoente; i++) {
        resultado *= base;
    }
    return resultado;
}

int main() {
    printf("Números de Armstrong de 3 algarismos na base 10:\n");

    for (int num = 100; num <= 999; num++) {
        int original = num;
        int somaPotencias = 0;
        int algarismo;

        while (original != 0) {
            algarismo = original % 10; // pega o último algarismo
            somaPotencias += calcularPotencia(algarismo, 3);
            original /= 10; // remove o último algarismo
        }

        if (num == somaPotencias) {
            printf("%d\n", num);
        }
    }

    return 0;
}
