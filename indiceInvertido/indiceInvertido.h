// indiceinvertido.h
#ifndef INDICEINVERTIDO_H
#define INDICEINVERTIDO_H

#include "hash.h"

typedef struct Documento
{
    char nome[50];
    struct Documento *proximo;
} Documento;

typedef struct NoPalavra
{
    char palavra[20];
    Documento *documentos;
    struct NoPalavra *proximo; // Para encadear palavras que colidam no mesmo slot
} NoPalavra;

typedef struct IndiceInvertido
{
    NoPalavra **tabela; // Vetor de ponteiros para NoPalavra
    int colisoes;       // Conta quantas vezes já existia uma chave no slot (colisão)
} IndiceInvertido;

IndiceInvertido *aloca();
void libera(IndiceInvertido *indice);
void insereDocumento(IndiceInvertido *indice, char *nomeDocumento, char *palavra);
NoPalavra *busca(IndiceInvertido *indice, char *palavra);
void consulta(IndiceInvertido *indice, char **palavras, int numPalavras);
void imprime(IndiceInvertido *indice);

#endif