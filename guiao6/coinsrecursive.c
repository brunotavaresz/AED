#include <stdio.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int maxCoinValue(int coins[], int n) {
    if (n == 0) {
        return 0;
    }
    if (n == 1) {
        return coins[0];
    }

    int withoutLast = maxCoinValue(coins, n - 1);
    int withLast = coins[n - 1] + maxCoinValue(coins, n - 2);

    return max(withoutLast, withLast);
}

int main() {
    int coins[] = {2, 4, 6, 8, 10};
    int n = sizeof(coins) / sizeof(coins[0]);

    int result = maxCoinValue(coins, n);
    printf("O valor máximo que pode ser obtido é: %d\n", result);

    return 0;
}
