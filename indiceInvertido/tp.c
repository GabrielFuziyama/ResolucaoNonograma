// tp.c
#include "indiceInvertido.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    int N;
    scanf("%d", &N);
    getchar(); // Consome o '\n'

    IndiceInvertido *indice = aloca();

    // Leitura dos documentos
    for (int i = 0; i < N; i++)
    {
        char linha[1000];
        fgets(linha, sizeof(linha), stdin);
        linha[strcspn(linha, "\n")] = 0;

        char *token = strtok(linha, " ");
        if (!token)
            continue;

        char nomeDoc[50];
        strcpy(nomeDoc, token);

        while ((token = strtok(NULL, " ")) != NULL)
        {
            insereDocumento(indice, nomeDoc, token);
        }
    }

    // Processamento das operações
    char operacao;
    while (scanf(" %c", &operacao) == 1)
    {
        if (operacao == 'B')
        {
            char buscaLinha[1000];
            getchar(); // Consome o '\n'
            fgets(buscaLinha, sizeof(buscaLinha), stdin);
            buscaLinha[strcspn(buscaLinha, "\n")] = 0;

            char *token = strtok(buscaLinha, " ");
            char *buscaPalavras[100];
            int numBusca = 0;
            while (token != NULL)
            {
                buscaPalavras[numBusca++] = token;
                token = strtok(NULL, " ");
            }

            consulta(indice, buscaPalavras, numBusca);
            printf("colisao = %d", indice->colisoes);
        }
        else if (operacao == 'I')
        {
            imprime(indice);
            printf("colisao = %d", indice->colisoes);
        }
    }

    libera(indice);
    return 0;
}