//CRIADO POR MATHEUS RIBEIRO | 26/JUN/2020 ====
//=============================================

//HEADER'S ====================================
#include "header.h"
//=============================================

//ALLOCATIONS =================================
double* alocar1DDouble(int tamanho) {
	double *vetor;
	vetor = (double*) calloc(tamanho, sizeof(double));
	return vetor;
}
void desalocar1DDouble(double *vetor) {
	free(vetor);
}
//=============================================
int* alocar1DInteger(int tamanho) {
	int *vetor;
	vetor = (int*) calloc(tamanho, sizeof(int));
	return vetor;
}
void desalocar1DInteger(int *vetor) {
	free(vetor);
}
//=============================================

// MAIN FUNCTION ==============================
void FillingTheQuadratureStruct(int N) {
	//DECLARAÇÃO DA QUADRATURA
	quadratura q;

	//VETORES PREENCHIDOS [4 QUADRANTES]
	q.w = GetWFullVector(N);
	q.eta = GetEtaFullVector(N);
	q.mi = GetMiFullVector(N);

	//TAMANHO DO VETOR COMPLETO [4 QUADRANTES]
	int size = N * (N + 2) / 2;
	int sizeQuad = size / 4;

	for (int n = 0; n < size; n++) {
		printf("ETA[%i] = %f - MI[%i] = %f - W[%i] = %f \n", n, q.eta[n], n,
				q.mi[n], n, q.w[n]);
		if (n == sizeQuad - 1 || n == 2 * sizeQuad - 1
				|| n == 3 * sizeQuad - 1) {
			printf("\n");
		}
	}

	desalocar1DDouble(q.w);
	desalocar1DDouble(q.eta);
	desalocar1DDouble(q.mi);
//=============================================
}

//BASE VECTOR'S ===============================
int* GetMappingBase(int N, int sizeQ) {
	int *map = alocar1DInteger(sizeQ);

	switch (N) {
	case 2:
		map[0] = 0;
		break;
	case 4:
		map[0] = 0;
		map[1] = 0;
		map[2] = 0;
		break;
	case 6:
		map[0] = 0;
		map[1] = 1;
		map[3] = 1;
		map[2] = 0;
		map[4] = 1;
		map[5] = 0;
		break;
	case 8:
		map[0] = 0;
		map[1] = 1;
		map[2] = 1;
		map[3] = 0;

		map[4] = 1;
		map[5] = 2;
		map[6] = 1;

		map[7] = 1;
		map[8] = 1;

		map[9] = 0;
		break;
	}

	return map;
}
//=============================================
double* GetMiBase(int N) {
//DECLARA O PONTEIRO PARA O MI =================================
	double *Mi;
//==============================================================

//ALOCANDO E PREENCHENDO OS VETORES ============================
	switch (N) {
	case 2:
		Mi = alocar1DDouble(1);
		Mi[0] = 0.5773502692;
		break;
	case 4:
		Mi = alocar1DDouble(2);
		Mi[0] = 0.3500212;
		Mi[1] = 0.8688903;
		break;
	case 6:
		Mi = alocar1DDouble(3);
		Mi[0] = 0.2666355;
		Mi[1] = 0.6815076;
		Mi[2] = 0.9261808;
		break;
	case 8:
		Mi = alocar1DDouble(4);
		Mi[0] = 0.2182179;
		Mi[1] = 0.5773503;
		Mi[2] = 0.7867958;
		Mi[3] = 0.9511897;
		break;
	}
//==============================================================

	return Mi;
}
//=============================================

//FULL VECTOR'S ===============================
double* GetMiFullVector(int N) {
	//TAMANHO DO VETOR COMPLETO [4 QUADRANTES]
	int size = N * (N + 2) / 2;
	//TAMANHO DO QUADRANTE
	int sizeQuad = size / 4;
	//TAMANHO DA PRIMEIRA COLUNA
	int colSize = N / 2;
	//TEMPORÁRIOS
	int ver = 0;

	//PADRÃO DE MI'S
	double *MIBase = GetMiBase(N);
	double *MI = alocar1DDouble(size);

	for (int n = 0; n < sizeQuad; n++) {
		if (ver == colSize) {
			colSize--;
			ver = 0;
		}
		//=============================
		MI[n] = MIBase[ver]; //  mi[0] = MI[0]
		//=============================
		MI[n + sizeQuad] = -MI[n];
		MI[n + 2 * sizeQuad] = -MI[n];
		MI[n + 3 * sizeQuad] = MI[n];
		//=============================
		ver++;
	}

	desalocar1DDouble(MIBase);

	return MI;
}
//=============================================
double* GetEtaFullVector(int N) {
	//TAMANHO DO VETOR COMPLETO [4 QUADRANTES]
	int size = N * (N + 2) / 2;
	//MI BASE
	double *MI = GetMiBase(N);
	double *ETA = alocar1DDouble(size);

	//TAMANHO DO QUADRANTE
	int sizeQuad = size / 4;
	//TAMANHO DA PRIMEIRA COLUNA
	int colSize = N / 2;

	//TEMPORÁRIOS
	int ver = 0;
	int x = 0;

	//INTERANDO E ARMAZENANDO OS ETA'S DE ACORDO COM O MAPEAMENTO DE MI'S
	for (int n = 0; n < sizeQuad; n++) {
		if (ver >= colSize) {
			x++;
			colSize--;
			ver = 0;
		}
		//=============================
		ETA[n] = MI[x];
		//=============================
		ETA[n + sizeQuad] = ETA[n];
		ETA[n + 2 * sizeQuad] = -ETA[n];
		ETA[n + 3 * sizeQuad] = -ETA[n];
		//=============================
		ver++;
	}

	desalocar1DDouble(MI);

	return ETA;
}
//=============================================
double* GetWFullVector(int N) {
	//TAMANHO DO VETOR
	int size = N * (N + 2) / 2;
	//TAMANHO DO QUADRANTE
	int sizeQuad = size / 4;

	//DECLARA OS PONTEIRO
	int *Mapping = GetMappingBase(N, sizeQuad);
	double *W = alocar1DDouble(size);
	double *WBase;

	//ALOCANDO E PREENCHENDO OS VETORES DE PESO BASE
	switch (N) {
	case 2:
		WBase = alocar1DDouble(1);
		WBase[0] = 1;
		break;
	case 4:
		WBase = alocar1DDouble(1);
		WBase[0] = 0.3333333;
		break;
	case 6:
		WBase = alocar1DDouble(2);
		WBase[0] = 0.1761263;
		WBase[1] = 0.1572071;
		break;
	case 8:
		WBase = alocar1DDouble(3);
		WBase[0] = 0.1209877;
		WBase[1] = 0.0907407;
		WBase[2] = 0.0925926;
		break;
	}

	//INTERANDO E ARMAZENANDO OS PESOS DE ACORDO COM O MAPEAMENTO
	for (int n = 0; n < sizeQuad; n++) {
		W[n] = WBase[Mapping[n]];
		//=============================
		W[n + sizeQuad] = W[n];
		W[n + 2 * sizeQuad] = W[n];
		W[n + 3 * sizeQuad] = W[n];
		//=============================
	}

	//DESALOCAÇÃO
	desalocar1DDouble(WBase);
	desalocar1DInteger(Mapping);

	return W;
}
//=============================================

/*DadosEntrada Ler(char nomeArquivo[]) {
	FILE *arq;
	DadosEntrada dado;

	// ABRE O ARQUIVO DE TEXTO PARA LEITURA
	arq = fopen(nomeArquivo, "rt");
	if (arq == NULL) {
		printf("Erro de Leitura");
		dado.numReg = 0;
		return dado;
	}

	while (fgets(contador, 100, arquivo) != NULL) {
		strcpy(tmpdados, contador);
		printf("\n%s", contador); //EXIBIR AS INFORMAÇÕES
	}
}*/
