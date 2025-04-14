#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "nonogram.h"

typedef struct nonograma
{
    int tamanho;
    int **tabuleiro;
    int **dicasLinhas;
    int **dicasColunas;
    int *qtdDicasLinhas;
    int *qtdDicasColunas;
    int *somaLinhas;
    int *somaColunas;
    int *preenchidosColuna; // Cache para células preenchidas por coluna
} Nonograma;

Nonograma *NonogramAllocate(int n)
{
    Nonograma *nono = (Nonograma *)malloc(sizeof(Nonograma));
    if (!nono)
        return NULL;

    nono->tamanho = n;
    nono->tabuleiro = (int **)malloc(n * sizeof(int *));
    nono->dicasLinhas = (int **)malloc(n * sizeof(int *));
    nono->dicasColunas = (int **)malloc(n * sizeof(int *));
    nono->qtdDicasLinhas = (int *)malloc(n * sizeof(int));
    nono->qtdDicasColunas = (int *)malloc(n * sizeof(int));
    nono->somaLinhas = (int *)calloc(n, sizeof(int));
    nono->somaColunas = (int *)calloc(n, sizeof(int));
    nono->preenchidosColuna = (int *)calloc(n, sizeof(int));

    for (int i = 0; i < n; i++)
    {
        nono->tabuleiro[i] = (int *)calloc(n, sizeof(int));
    }
    return nono;
}

void NonogramFree(Nonograma *tab)
{
    if (!tab)
        return;
    for (int i = 0; i < tab->tamanho; i++)
    {
        free(tab->tabuleiro[i]);
        free(tab->dicasLinhas[i]);
        free(tab->dicasColunas[i]);
    }
    free(tab->tabuleiro);
    free(tab->dicasLinhas);
    free(tab->dicasColunas);
    free(tab->qtdDicasLinhas);
    free(tab->qtdDicasColunas);
    free(tab->somaLinhas);
    free(tab->somaColunas);
    free(tab->preenchidosColuna);
    free(tab);
}

void NonogramRead(Nonograma *tab)
{
    for (int i = 0; i < tab->tamanho; i++)
    {
        scanf("%d", &tab->qtdDicasColunas[i]);
        tab->dicasColunas[i] = (int *)malloc(tab->qtdDicasColunas[i] * sizeof(int));
        tab->somaColunas[i] = 0;
        for (int j = 0; j < tab->qtdDicasColunas[i]; j++)
        {
            scanf("%d", &tab->dicasColunas[i][j]);
            tab->somaColunas[i] += tab->dicasColunas[i][j];
        }
    }

    for (int i = 0; i < tab->tamanho; i++)
    {
        scanf("%d", &tab->qtdDicasLinhas[i]);
        tab->dicasLinhas[i] = (int *)malloc(tab->qtdDicasLinhas[i] * sizeof(int));
        tab->somaLinhas[i] = 0;
        for (int j = 0; j < tab->qtdDicasLinhas[i]; j++)
        {
            scanf("%d", &tab->dicasLinhas[i][j]);
            tab->somaLinhas[i] += tab->dicasLinhas[i][j];
        }
    }
}

void NonogramPrint(Nonograma *tab)
{
    for (int i = 0; i < tab->tamanho; i++)
    {
        for (int j = 0; j < tab->tamanho; j++)
        {
            printf("%c ", tab->tabuleiro[i][j] ? 'x' : '.');
        }
        printf("\n");
    }
}

// Verifica se uma linha está válida em O(n)
int verificaLinha(int *linha, int *dicas, int qtdDicas, int tamanho, int somaEsperada)
{
    int grupo = 0, contador = 0, soma = 0;

    for (int j = 0; j < tamanho; j++)
    {
        if (linha[j])
        {
            contador++;
            soma++;
        }
        else if (contador > 0)
        {
            if (grupo >= qtdDicas || contador != dicas[grupo])
                return 0;
            grupo++;
            contador = 0;
        }
    }

    if (contador > 0)
    {
        if (grupo >= qtdDicas || contador != dicas[grupo])
            return 0;
        grupo++;
    }

    return grupo == qtdDicas && soma == somaEsperada;
}

// Verifica se uma coluna está válida até determinada linha em O(n)
int verificaColunaParcial(Nonograma *tab, int col, int linhaAtual)
{
    int grupo = 0, contador = 0;
    int *dicas = tab->dicasColunas[col];
    int qtdDicas = tab->qtdDicasColunas[col];

    if (tab->preenchidosColuna[col] > tab->somaColunas[col])
        return 0;

    for (int i = 0; i <= linhaAtual; i++)
    {
        if (tab->tabuleiro[i][col])  
        {
            contador++;
        }
        else if (contador > 0)
        {
            if (grupo >= qtdDicas || contador > dicas[grupo])
                return 0;
            grupo++;
            contador = 0;
        }
    }

    if (contador > 0)
    {
        if (grupo >= qtdDicas || contador > dicas[grupo])
            return 0;
    }

    return 1;
}

void preencherLinha(Nonograma *tab, int linha, int pos, int *solucoes)
{
    if (pos == tab->tamanho)
    {
        if (!verificaLinha(tab->tabuleiro[linha], tab->dicasLinhas[linha],
                           tab->qtdDicasLinhas[linha], tab->tamanho, tab->somaLinhas[linha]))
            return;

        if (linha == tab->tamanho - 1)
        {
            for (int j = 0; j < tab->tamanho; j++)
            {
                if (!verificaColunaParcial(tab, j, linha))
                    return;
            }
            (*solucoes)++;
            printf("SOLUTION %d:\n", *solucoes);
            NonogramPrint(tab);
            return;
        }

        preencherLinha(tab, linha + 1, 0, solucoes);
        return;
    }

    // Tenta colocar 0
    tab->tabuleiro[linha][pos] = 0;
    if (verificaColunaParcial(tab, pos, linha))
    {
        preencherLinha(tab, linha, pos + 1, solucoes);
    }

    // Tenta colocar 1
    tab->tabuleiro[linha][pos] = 1;
    tab->preenchidosColuna[pos]++;
    if (verificaColunaParcial(tab, pos, linha))
    {
        preencherLinha(tab, linha, pos + 1, solucoes);
    }
    tab->preenchidosColuna[pos]--;
    tab->tabuleiro[linha][pos] = 0;
}

int NonogramPlay(Nonograma *tab)
{
    int solucoes = 0;
    preencherLinha(tab, 0, 0, &solucoes);

    if (solucoes == 0)
    {
        printf("No solution was found!\n");
    }
    else
    {
        printf("Total of solutions: %d\n", solucoes);
    }

    return solucoes;
}
