#include "main.h"

int main(int argc, char *argv[]) {

	setlocale(LC_ALL,"");

	if (argc != 3) {
		printf("Parâmetros inválidos!\n");
		return 1;
	}
	
	
	int qtd;
	char palavra[50];
	
	PonteiroNo raiz = encheArvore(argv[1]); // Carrega a árvore na raiz.
	
	system("clear");
	printf("Digite 0 (zero) para sair\n");

	while(1) {
	
		printf("Digite a palavra: ");
		fgets(palavra, 50, stdin);
		
		if (palavra[0] == '0') {
			break;
		}

		qtd = atoi(argv[2]);
		
		busca(palavra, raiz, 0, &qtd);
	}
	
	return 0;
}

