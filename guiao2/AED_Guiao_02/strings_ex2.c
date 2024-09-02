#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(void)
{
    // pedir ao utilizador para inserir uma string
    char str[100];
    printf("Insira uma string: ");
    scanf("%s", str);

    // pedir ao utilizador para inserir outra string
    char str2[100];
    printf("Insira outra string: ");
    scanf("%s", str2);

    // Conte os caracteres da primeira string que são letras do alfabeto.
    int count = 0;
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (isalpha(str[i]))
        {
            count++;
        }
        
    }
    

    // Conte os caracteres da segunda string que são letras maiúsculas.
    int count2 = 0;
    for (int i = 0; str2[i] != '\0'; i++)
    {
        if (isupper(str2[i]))
        {
            count2++;
        }
    }

    printf("A primeira string tem %d\n", count);
    printf("A segunda string tem %d maiúsculas\n", count2);

    // Converta todas as letras maiúsculas, das duas strings, para minúsculas.
    for (int i = 0; str[i] != '\0'; i++)
    {
        str[i] = tolower(str[i]);
    }

    for (int i = 0; str2[i] != '\0'; i++)
    {
        str2[i] = tolower(str2[i]);
    }
    
    
    // Compare as duas strings resultantes e escreva uma mensagem indicando que são iguais, ou apresentando as duas strings na sua ordem lexicográfica.

    if (strlen(str) < strlen(str2))
    {
        printf("A primeira string é menor que a segunda string.\n");

    }
    else if (strlen(str) > strlen(str2))
    {
        printf("A primeira string é maior que a segunda string.\n");

    }
    else
    {
        printf("São iguais quanto ao tamanho.\n");
    }



    // Junte a primeira string com a segunda
    strcat(str, str2);
    
    printf("Concatenada: %s\n", str); 


    return 0;

}