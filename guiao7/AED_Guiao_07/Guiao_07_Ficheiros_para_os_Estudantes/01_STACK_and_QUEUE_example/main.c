#include <stdio.h>
#include "IntegersQueue.h"
#include "IntegersStack.h"

int main() {
    Queue* queue = QueueCreate(20); //alocar memoria para a queue
    Stack* stack = StackCreate(20); //alocar memoria para a stack

    printf("Enter a positive integer: ");
    int num;
    scanf("%d", &num);

    int originalNum = num;
    while (num > 0) {
        int digit = num % 10; //obter o ultimo digito
        QueueEnqueue(queue, digit); //adicionar o ultimo digito a queue
        StackPush(stack, digit);  //adicionar o ultimo digito a stack
        num /= 10; //remover o ultimo digito
    }

    int isPalindrome = 1;
    while (!QueueIsEmpty(queue) && !StackIsEmpty(stack)) { //enquanto a queue e a stack nao estiverem vazias
        int queueDigit = QueueDequeue(queue); //obter o primeiro digito da queue
        int stackDigit = StackPop(stack); //obter o ultimo digito da stack
        if (queueDigit != stackDigit) { //se os digitos forem diferentes
            isPalindrome = 0; //nao e palindrome
            break;
        }
    }

    if (isPalindrome) {
        printf("%d is a palindrome.\n", originalNum);
    } else {
        printf("%d is not a palindrome.\n", originalNum);
    }

    QueueDestroy(&queue); //libertar memoria da queue
    StackDestroy(&stack); //libertar memoria da stack

    return 0;
}

