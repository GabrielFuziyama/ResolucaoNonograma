#include <stdio.h>
#include "nonogram.h"

int main()
{
    int tamanho;
    // printf("Digite o tamanho do tabuleiro: ");
    scanf("%d", &tamanho);

    Nonograma *nono = NonogramAllocate(tamanho);
    if (nono == NULL)
    {
        return 1;
    }

    // printf("Digite as dicas das linhas e colunas:\n");
    NonogramRead(nono);

    printf("\nResolvendo o Nonograma...\n");
    NonogramPlay(nono);

    Nonogramfree(nono);
    return 0;
}
