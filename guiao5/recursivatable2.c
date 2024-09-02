#include <stdio.h>

// Função para calcular T1
int T1(int n, int *count1) { // count1 é um ponteiro para um inteiro
    if (n == 1) { // Caso base
        return 1;
    } else {
        int result = T1(n / 2, count1) + n; // Chamada recursiva
        (*count1)++; // Contador de chamadas recursivas
        return result; // Retorno do resultado
    }
}

// Função para calcular T2
int T2(int n, int *count2) { // count2 é um ponteiro para um inteiro
    if (n == 1) { // Caso base
        return 1;
    } else {
        int result = T2(n / 2, count2) + T2((n + 1) / 2, count2) + n; // Chamada recursiva
        (*count2)++; // Contador de chamadas recursivas
        return result; // Retorno do resultado
    }
}

// Função para calcular T3
int T3(int n, int *count3) { // count3 é um ponteiro para um inteiro
    if (n == 1) { // Caso base
        return 1;
    } else if (n % 2 == 0) { // Caso n seja par
        int result = 2 * T3(n / 2, count3) + n; // Chamada recursiva
        (*count3)++; // Contador de chamadas recursivas
        return result;
    } else { // Caso n seja ímpar
        int result = T3(n / 2, count3) + T3((n + 1) / 2, count3) + n; // Chamada recursiva
        (*count3)++; // Contador de chamadas recursivas
        return result;
    }
}

int main() {
    int N;
    printf("Digite o valor de N: ");
    scanf("%d", &N); // Lê o valor de N do teclado e armazena na variável N

    printf("N\tT1(N)\tChamadas\tT2(N)\tChamadas\tT3(N)\tChamadas\n"); // Imprime o cabeçalho da tabela

    for (int i = 1; i <= N; i++) { // Para cada valor de i entre 1 e N, inclusive
        int count1 = 0, count2 = 0, count3 = 0; // Inicializa os contadores de chamadas recursivas

        int result1 = T1(i, &count1); // Calcula T1(i) e armazena o resultado em result1
        int result2 = T2(i, &count2); // Calcula T2(i) e armazena o resultado em result2
        int result3 = T3(i, &count3); // Calcula T3(i) e armazena o resultado em result3

        printf("%d\t%d\t%d\t\t%d\t%d\t\t%d\t%d\n", i, result1, count1, result2, count2, result3, count3); // Imprime os resultados
    }

    return 0;
}

