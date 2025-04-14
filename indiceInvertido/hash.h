// hash.h
#ifndef HASH_H
#define HASH_H

#define TAMANHO_HASH 1009 // Número primo para minimizar colisões
#define MAX_PALAVRA 20    // Máximo de caracteres por palavra

int h(char *chave, int m); // Função hash principal
int hash2(char *palavra);  // Função hash secundária (para hashing duplo)

#endif