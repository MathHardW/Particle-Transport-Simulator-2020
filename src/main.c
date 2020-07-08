//CRIADO POR MATHEUS RIBEIRO | 26/JUN/2020 ========================
//=================================================================
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include "header.h"
//=================================================================
int main(int argc, char *argv[]) {
	//int N = 8;
	//FillingTheQuadratureStruct(N);

	//===========================================================
	FILE *arq;
	char nomeArquivo[] = "/home/matheus/Documentos/1 - Code/7 - Projeto_de_Pesquisa_2020/PDP2020/src/DataFiles/Dados1.txt";
	// ABRE O ARQUIVO DE TEXTO PARA LEITURA
	arq = fopen(nomeArquivo, "rt");
	if (arq == NULL) {printf("Erro de Leitura");return 0;}
	//===========================================================

	//===========================================================
	//CONTADOR PARA LINHA
	int l = 0;
	//LÊ O VALOR DAS LINHA
	char Linha[100];
	//GUARDA O VALOR A SER UTILIZADO
	char **LinhaDado = malloc(150 * sizeof(char*));
	//===========================================================
	while (l < 9) {
		fgets(Linha, 100, arq);

		if (fgets(Linha, 100, arq)) {
			LinhaDado[l] = malloc(strlen(Linha) * sizeof(char*));
			strcpy(LinhaDado[l], Linha);
			printf("%s", LinhaDado[l]);
			l++;
		}
	}
	//===========================================================


	return 0;
}
