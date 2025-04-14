#include <stdlib.h>
#include "nonogram.h"

struct Nonograma
{
    int *tam_Linhas;
    int *tam_Colunas;
    int **Colunas;
    int **Linhas;
    int tam;
};

Nonograma NonogramAllocate(int n)
{
    Nonograma *nono;
    nono->tam_Linhas = (int *)malloc(n * sizeof(int));
    nono->tam_Colunas = (int *)malloc(n * sizeof(int));
    nono->Linhas = (int **)malloc(n * sizeof(int *));
    nono->Colunas = (int **)malloc(n * sizeof(int *));
    nono->tam = n;
    return nono;
}

void Nonogramfree(Nonograma *tab)
{
    for (int i = 0; i < tab->tam; i++)
    {
        free(linhas[i]);
        free(colunas[i]);
    }
    free(linhas);
    free(colunas);
    free(tam_linhas);
    free(tam_colunas);
    return NULL;
}

void NonogramRead(Nonograma *tab)
{
    int tam = 0;
    for (int i = 0; i < tab->tam; i++)
    {
        scanf("%d", &tam);                                 // le o tamanho da linha
        tab->tam_Linhas[i] = tam;                          // Armazena o tamanho da linha
        tab->Linhas[i] = (int *)malloc(tam * sizeof(int)); // alloca a linha
        for (int j = 0; j < tam; j++)
        {
            scanf("%d", &tab->Linhas[i][j]); // le a linhas
        }
    }
    for (int i = 0; i < tab->tam; i++)
    {
        scanf("%d", &tam);                                  // le o tamanho da linha
        tab->tam_Colunas[i] = tam;                          // Armazena o tamanho da coluna
        tab->Colunas[i] = (int *)malloc(tam * sizeof(int)); // alloca a linha
        for (int j = 0; j < tam; j++)
        {
            scanf("%d", &tab->Colunas[i][j]); // le a linhas
        }
    }
}
