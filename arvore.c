#include "arvore.h"

// Inicia o nó
PonteiroNo iniciaNo(char c) {
	PonteiroNo no = (PonteiroNo) malloc(sizeof(NoChar));
	if (no==NULL) {
		return NULL;
	}
	no->chave = c;
	int i;
	no->letras = (PonteiroNo *) malloc(sizeof(PonteiroNo));
	no->palavra = NULL;
	no->qtdLetras = 0;
	return no;
}

// Insere um nó com o char c como chave se o pai não tiver o filho específico
PonteiroNo insereNo(PonteiroNo pai, char c) {
	int i=-1; 
	PonteiroNo filho;
	int j;
	for (j=0; j<pai->qtdLetras; j++) {
		if (pai->letras[j]->chave == toLower(c)) {
			i = j;
			break;
		}
	}

	if (i==-1)  {
		i++;
		filho = iniciaNo(toLower(c));
		pai->letras = (PonteiroNo *) realloc (pai->letras, (pai->qtdLetras+1)*sizeof(PonteiroNo));
		pai->letras[pai->qtdLetras] = filho;
		
		if (pai->qtdLetras>1) {
			if (toIndex(pai->letras[pai->qtdLetras-1]->chave) > toIndex(pai->letras[pai->qtdLetras]->chave)) {
				ordenaLetras(pai->letras, pai->qtdLetras);
			}
		}
		
		pai->qtdLetras++;
	} else {
		filho = pai->letras[i];
		
	}

	return filho;
}

// Ordena as letras no vetor dos nós filhos.
void ordenaLetras(PonteiroNo *letras, short int i) {
	
	PonteiroNo aux;

	i--;
	while ((i>=0) && (toIndex(letras[i]->chave) > toIndex(letras[i+1]->chave))) {
	
		aux = letras[i];
		letras[i] = letras[i+1];
		letras[i+1] = aux;
		i--;

	}
}

// Carrega a árvore com o arquivo passado em arq
PonteiroNo encheArvore(char *arq) {

	FILE *dicionario;
	dicionario = fopen(arq, "r");
	if (dicionario == NULL) {
		printf("Arquivo inválido\n");
		return NULL;
	}
	
	PonteiroNo raiz;
	raiz = iniciaNo('\0');
	
	PonteiroNo pai;
	pai = raiz;
	char c;
	char string[TAM_PALAVRA];
	int i=0;
	
	while ( (c = fgetc(dicionario)) != EOF ) {
		if (c == '/') {
			c = fgetc(dicionario);
			continue;
		}
		if (c == '\n') {
			pai = raiz;
			continue;
		}
		
		pai = insereNo(pai, c);
		string[i++]=c;
		while ( (c = fgetc(dicionario)) != '\n' ) {
			if (c == '/') {
				c = fgetc(dicionario);	
				break;
			}
			
			pai = insereNo(pai, c);
			string[i++]=c;
		}
		
		string[i++] = '\0';		
		pai->palavra = (char *) realloc(pai->palavra, (sizeof(char)*strlen(string))+1);
		strcpy(pai->palavra, string);

		pai = raiz;
		i=0;
	}
	
	fclose(dicionario);
	
	return raiz;
	
}

// Torna as letras maiúsculas em minúsculas
char toLower(char c) {
	if ((c>=65) && (c<=90)) {
		return c+32;
	}
	if ((c>=97) && (c<=122)) {
		return c;
	}
	return c;
}

int toIndex(char c) {
	if ((c>=65) && (c<=90)) {
		return c-65;
	}
	if ((c>=97) && (c<=122)) {
		return c-97;
	}
	return c;
}

// Faz a busca na árvore e desce até achar as letras digitadas
void busca(char *palavrita, PonteiroNo no, int index, int *qtdAImprimir){	
	printf("no %c", no->chave);

	int j, i=-1;	
	int k = no->qtdLetras;
	for (j=0; j<k; j++) {
		if (no->letras[j]->chave == toLower(palavrita[index])) {
			i = j;
			break;
		}
	}

	if (i!=-1) {

		if (index+2 == strlen(palavrita)) {
			imprimeProximos(no->letras[i], qtdAImprimir);
		} else {
			busca(palavrita, no->letras[i], index+1, qtdAImprimir);
		}
		
	}

}

// Imprime as n primeiras palavras abaixo do nó atual
void imprimeProximos(PonteiroNo no, int *qtdAImprimir) {
	
	if (no->palavra != NULL) {
		printf("%s\n", no->palavra);
		*qtdAImprimir = *qtdAImprimir - 1;
	}
	
	int i;
	for (i=0; (i<no->qtdLetras) && (*qtdAImprimir>0); i++) {
		imprimeProximos(no->letras[i], qtdAImprimir);
	}
}
