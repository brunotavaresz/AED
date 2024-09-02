#include <stdio.h>

// Função para calcular T1
int T1(int n, int *count1) {
    if (n == 1) {
        return 1;
    } else {
        int result = T1(n / 2, count1) + n;
        (*count1)++;
        return result;
    }
}

// Função para calcular T2
int T2(int n, int *count2) {
    if (n == 1) {
        return 1;
    } else {
        int result = T2(n / 2, count2) + T2((n + 1) / 2, count2) + n;
        (*count2)++;
        return result;
    }
}

// Função para calcular T3
int T3(int n, int *count3) {
    if (n == 1) {
        return 1;
    } else if (n % 2 == 0) {
        int result = 2 * T3(n / 2, count3) + n;
        (*count3)++;
        return result;
    } else {
        int result = T3(n / 2, count3) + T3((n + 1) / 2, count3) + n;
        (*count3)++;
        return result;
    }
}

int main() {
    int N;
    printf("Digite o valor de N: ");
    scanf("%d", &N);

    printf("N\tT1(N)\tChamadas  T2(N)\tChamadas  T3(N)\tChamadas\n");

    for (int i = 1; i <= N; i++) {
        int count1 = 0, count2 = 0, count3 = 0;

        int result1 = T1(i, &count1);
        int result2 = T2(i, &count2);
        int result3 = T3(i, &count3);

        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", i, result1, count1, result2, count2, result3, count3);
    }

    return 0;
}
