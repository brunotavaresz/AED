#include <stdio.h>

int calcularFatorial(int n) { 
    int resultado = 1; // 0! = 1
    for (int i = 1; i <= n; i++) { // 1! = 1, 2! = 1*2, 3! = 1*2*3, ...
        resultado *= i; // resultado = resultado * i;
    }
    return resultado;
}

int eFactoriao(int numero) { // 145 = 1! + 4! + 5!
    int original = numero; // guardar o valor original para comparar no fim
    int somaFatoriais = 0; // soma dos fatoriais dos dígitos
    
    while (numero > 0) { // enquanto houver dígitos
        int digito = numero % 10; // obter o último dígito
        somaFatoriais += calcularFatorial(digito); // somar o fatorial do dígito
        numero /= 10; // remover o último dígito
    }
    
    return somaFatoriais == original; // se a soma dos fatoriais for igual ao original, é factoriao
}

int main() {
    printf("Factoriões menores que 10^6: ");
    
    for (int num = 1; num < 1000000; num++) {
        if (eFactoriao(num)) {
            printf("%d ", num);
        }
    }
    
    printf("\n");

    return 0;
}
