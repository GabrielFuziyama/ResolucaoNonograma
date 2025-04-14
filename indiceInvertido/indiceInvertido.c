// indiceinvertido.c
#include "indiceInvertido.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Aloca memória para o índice invertido
IndiceInvertido *aloca()
{
    IndiceInvertido *indice = malloc(sizeof(IndiceInvertido));
    indice->tabela = calloc(TAMANHO_HASH, sizeof(NoPalavra *)); // Inicializa com NULL
    indice->colisoes = 0;
    return indice;
}

// Libera memória do índice invertido
void libera(IndiceInvertido *indice)
{
    for (int i = 0; i < TAMANHO_HASH; i++)
    {
        NoPalavra *no = indice->tabela[i];
        while (no != NULL)
        {
            NoPalavra *tempNo = no;
            // Libera a lista de documentos
            Documento *doc = tempNo->documentos;
            while (doc != NULL)
            {
                Documento *tempDoc = doc;
                doc = doc->proximo;
                free(tempDoc);
            }
            no = no->proximo;
            free(tempNo);
        }
    }
    free(indice->tabela);
    free(indice);
}

// Insere um documento associado a uma palavra utilizando hashing duplo
void insereDocumento(IndiceInvertido *indice, char *nomeDocumento, char *palavra)
{
    int pos = h(palavra, TAMANHO_HASH); // Hashing principal
    int passo = hash2(palavra);         // Hashing secundário
    int inicio = pos;

    // Calcula a posição inicial usando hashing duplo
    while (indice->tabela[pos] != NULL && strcmp(indice->tabela[pos]->palavra, palavra) != 0)
    {
        pos = (pos + passo) % TAMANHO_HASH;
        if (pos == inicio)
        { // Tabela cheia (caso raro)
            printf("Erro: Tabela hash cheia!\n");
            exit(1);
        }
    }

    // Se a palavra já existe na posição calculada
    if (indice->tabela[pos] != NULL && strcmp(indice->tabela[pos]->palavra, palavra) == 0)
    {
        NoPalavra *atual = indice->tabela[pos];

        // Verifica se o documento já está na lista
        Documento *doc = atual->documentos;
        while (doc != NULL)
        {
            if (strcmp(doc->nome, nomeDocumento) == 0)
                return; // Documento já inserido
            doc = doc->proximo;
            (indice)->colisoes++;
        }

        // Insere o novo documento ao final da lista de documentos
        Documento *novoDoc = malloc(sizeof(Documento));
        strcpy(novoDoc->nome, nomeDocumento);
        novoDoc->proximo = NULL;

        if (atual->documentos == NULL)
        {
            atual->documentos = novoDoc;
        }
        else
        {
            Documento *ultimo = atual->documentos;
            while (ultimo->proximo != NULL)
                ultimo = ultimo->proximo;
            ultimo->proximo = novoDoc;
        }
        return;
    }

    // Se chegou aqui, a palavra não existe: cria um novo nó
    NoPalavra *novoNo = malloc(sizeof(NoPalavra));
    strcpy(novoNo->palavra, palavra);
    novoNo->documentos = NULL;

    // Insere o documento no novo nó
    Documento *novoDoc = malloc(sizeof(Documento));
    strcpy(novoDoc->nome, nomeDocumento);
    novoDoc->proximo = NULL;
    novoNo->documentos = novoDoc;

    // Insere o novo nó no início da lista encadeada
    novoNo->proximo = indice->tabela[pos];
    indice->tabela[pos] = novoNo;

    // Atualiza contador de colisões
    if (indice->tabela[pos]->proximo != NULL)
        indice->colisoes++;
}

// Busca uma palavra na tabela (percorre a lista encadeada do slot)
NoPalavra *busca(IndiceInvertido *indice, char *palavra)
{
    int pos = h(palavra, TAMANHO_HASH); // Hashing principal
    int passo = hash2(palavra);         // Hashing secundário
    int inicio = pos;

    // Percorre a tabela usando hashing duplo
    while (indice->tabela[pos] != NULL)
    {
        if (strcmp(indice->tabela[pos]->palavra, palavra) == 0)
        {
            return indice->tabela[pos];
        }
        pos = (pos + passo) % TAMANHO_HASH;
        if (pos == inicio)
            break; // Voltou ao início: palavra não encontrada
    }
    return NULL;
}

// Consulta documentos que contêm todas as palavras (operação "B")
void consulta(IndiceInvertido *indice, char **palavras, int numPalavras)
{
    NoPalavra *entradas[numPalavras];
    for (int i = 0; i < numPalavras; i++)
    {
        entradas[i] = busca(indice, palavras[i]);
        if (entradas[i] == NULL)
        {
            printf("none\n");
            return;
        }
    }

    // Obtém os documentos da primeira palavra
    char *documentos[100];
    int numDocs = 0;
    Documento *doc = entradas[0]->documentos;
    while (doc != NULL)
    {
        documentos[numDocs++] = doc->nome;
        doc = doc->proximo;
    }

    // Realiza a interseção dos documentos para as demais palavras
    for (int i = 1; i < numPalavras; i++)
    {
        int novoNumDocs = 0;
        for (int j = 0; j < numDocs; j++)
        {
            Documento *temp = entradas[i]->documentos;
            while (temp != NULL)
            {
                if (strcmp(temp->nome, documentos[j]) == 0)
                {
                    documentos[novoNumDocs++] = documentos[j];
                    break;
                }
                temp = temp->proximo;
            }
        }
        numDocs = novoNumDocs;
        if (numDocs == 0)
        {
            printf("none\n");
            return;
        }
    }

    // Ordena lexicograficamente os documentos
    for (int i = 0; i < numDocs - 1; i++)
    {
        for (int j = i + 1; j < numDocs; j++)
        {
            if (strcmp(documentos[i], documentos[j]) > 0)
            {
                char *temp = documentos[i];
                documentos[i] = documentos[j];
                documentos[j] = temp;
            }
        }
    }

    // Imprime os documentos ordenados
    for (int i = 0; i < numDocs; i++)
    {
        printf("%s\n", documentos[i]);
    }
}

// Imprime o índice invertido (operação "I")
void imprime(IndiceInvertido *indice)
{
    for (int i = 0; i < TAMANHO_HASH; i++)
    {
        if (indice->tabela[i] != NULL)
        {
            NoPalavra *atual = indice->tabela[i];
            while (atual != NULL)
            {
                printf("%s - ", atual->palavra);
                Documento *doc = atual->documentos;
                while (doc != NULL)
                {
                    printf("%s", doc->nome);
                    if (doc->proximo != NULL)
                        printf(" ");
                    doc = doc->proximo;
                }
                printf("\n");
                atual = atual->proximo;
            }
        }
    }
}