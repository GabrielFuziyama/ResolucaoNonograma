// hash.c
#include "hash.h"
#include <string.h>

// Função hash principal
int h(char *chave, int m)
{
    float p[] = {0.8326030060567271, 0.3224428884580177,
                 0.6964223353369197, 0.1966079596929834,
                 0.8949283476433433, 0.4587297824155836,
                 0.5100785238948532, 0.05356055934904358,
                 0.9157270141062215, 0.7278472432221632};
    int tamP = 10;
    unsigned int soma = 0;
    for (int i = 0; i < (int)strlen(chave); i++)
        soma += (unsigned int)chave[i] * p[i % tamP];
    return soma % m;
}

// Função hash secundária (para análise complementar, não usada para sondagem)
int hash2(char *palavra)
{
    unsigned int valor = 0;
    for (int i = 0; palavra[i] != '\0'; i++)
    {
        valor = valor * 37 + palavra[i];
    }
    return 1 + (valor % (TAMANHO_HASH - 1)); // Valor entre 1 e m-1
}