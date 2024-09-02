#include <stdio.h>

// Função recursiva para calcular o número de Delannoy D(m, n)
int delannoy_recursive(int m, int n) {
    if (m == 0 || n == 0) {
        return 1;
    } else {
        return delannoy_recursive(m - 1, n) + delannoy_recursive(m - 1, n - 1) + delannoy_recursive(m, n - 1);
    }
}

// Função iterativa usando Programação Dinâmica e um array 2D local
int delannoy_dp(int m, int n) {
    int dp[m + 1][n + 1];

    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0 || j == 0) {
                dp[i][j] = 1;
            } else {
                dp[i][j] = dp[i - 1][j] + dp[i - 1][j - 1] + dp[i][j - 1];
            }
        }
    }

    return dp[m][n];
}

// Função recursiva usando memoization e um array 2D global
int memoization_table[100][100]; // Ajuste o tamanho conforme necessário

int delannoy_memoization(int m, int n) {
    if (m == 0 || n == 0) {
        return 1;
    }

    if (memoization_table[m][n] != -1) {
        return memoization_table[m][n];
    }

    memoization_table[m][n] = delannoy_memoization(m - 1, n) + delannoy_memoization(m - 1, n - 1) + delannoy_memoization(m, n - 1);
    return memoization_table[m][n];
}

int main() {
    int m, n;
    printf("Informe os valores de m e n: ");
    scanf("%d %d", &m, &n);

    // Inicializa a tabela de memoization com -1
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            memoization_table[i][j] = -1;
        }
    }

    // Imprime o número de Delannoy para os valores de m e n
    printf("O número de Delannoy D(%d, %d) é %d (Recursivo)\n", m, n, delannoy_recursive(m, n));
    printf("O número de Delannoy D(%d, %d) é %d (Programação Dinâmica)\n", m, n, delannoy_dp(m, n));
    printf("O número de Delannoy D(%d, %d) é %d (Memoization)\n", m, n, delannoy_memoization(m, n));

    // Tabela de Delannoy formatada
    printf("Tabela de Delannoy:\n");
    printf("    ");
    for (int i = 0; i <= n; i++) {
        printf("%8d", i);
    }
    printf("\n");
    for (int i = 0; i <= m; i++) {
        printf("%4d", i);
        for (int j = 0; j <= n; j++) {
            printf("%8d", delannoy_dp(i, j));
        }
        printf("\n");
    }

    return 0;
}
