#ifndef ARVORE_H
#define ARVORE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_PALAVRA 100

typedef struct NoChar *PonteiroNo;

typedef struct NoChar {
	char chave;
	char *palavra;
	PonteiroNo *letras;
	short int qtdLetras;
} NoChar;

PonteiroNo iniciaNo(char c);

PonteiroNo insereNo(PonteiroNo pai, char c);

void ordenaLetras(PonteiroNo *letras, short int i);

PonteiroNo encheArvore(char *arq);

char toLower(char c);

int toIndex(char c);

void busca(char *palavrita, PonteiroNo no, int index, int *qtdAImprimir);

void imprimeProximos(PonteiroNo no, int *qtdAImprimir);

#endif
