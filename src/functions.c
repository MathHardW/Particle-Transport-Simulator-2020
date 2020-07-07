//CRIADO POR MATHEUS RIBEIRO | 26/JUN/2020 ========================
//=================================================================
#include "header.h"

//ALOCAÇÕES========================================================
double* alocar1DDouble(int tamanho) {
	double *vetor;
	vetor = (double*) calloc(tamanho, sizeof(double));
	return vetor;
}
void desalocar1DDouble(double *vetor) {
	free(vetor);
}

int* alocar1DInteger(int tamanho) {
	int *vetor;
	vetor = (int*) calloc(tamanho, sizeof(int));
	return vetor;
}
void desalocar1DInteger(int *vetor) {
	free(vetor);
}
//=================================================================

//FUNCTIONS =======================================================
void FillingTheQuadratureStruct(int N) {

	//TAMANHO DO VETOR COMPLETO [4 QUADRANTES]
	int size = N * (N + 2) / 2;                        //40

	//MAPEAMENTO DO VETOR
	int *Mapping = GetMapping(N, size / 4);

	//PADRÃO DE PESOS
	double *W = GetWforQuadrature(N);

	//PADRÃO DE MI'S
	double *MI = GetMiforQuadrature(N);

	//DECLARAÇÃO DA QUADRATURA
	quadratura q;

	//ALOCAÇÕES DA QUADRATURA
	q.w = alocar1DDouble(size);
	q.mi = alocar1DDouble(size);
	q.eta = alocar1DDouble(size);

	//TAMANHO DO QUADRANTE
	int sizeQuad = size / 4;                      //10
	//TAMANHO DA PRIMEIRA COLUNA
	int colSize = N / 2;                         //4

	//TEMPORÁRIOS
	int ver = 0;
	int x = 0;

	//n ============================================================
	for (int n = 0; n < sizeQuad; n++) {
		if (ver >= colSize) {
			x++;
			colSize--;
			ver = 0;
		}
		//=============================
		q.eta[n] = MI[x];
		//=============================
		q.eta[n + sizeQuad] = q.eta[n];
		q.eta[n + 2 * sizeQuad] = -q.eta[n];
		q.eta[n + 3 * sizeQuad] = -q.eta[n];
		//=============================
		ver++;

	}

	//printf("\n\n");

	//PESO =========================================================
	for (int n = 0; n < sizeQuad; n++) {
		q.w[n] = W[Mapping[n]];
		//=============================
		q.w[n + sizeQuad] = q.w[n];
		q.w[n + 2 * sizeQuad] = q.w[n];
		q.w[n + 3 * sizeQuad] = q.w[n];
		//=============================
		//printf("%i | %i | W = %f \n", n, Mapping[n], q.w[n]);
	}

	//printf("\n\n");

	//MI ==============================================================
	ver = 0;
	colSize = N / 2;
	for (int n = 0; n < sizeQuad; n++) {
		if (ver == colSize) {
			colSize--;
			ver = 0;
		}
		//=============================
		q.mi[n] = MI[ver]; //  mi[0] = MI[0]
		//=============================
		q.mi[n + sizeQuad] = -q.mi[n];
		q.mi[n + 2 * sizeQuad] = -q.mi[n];
		q.mi[n + 3 * sizeQuad] = q.mi[n];
		//=============================
		//printf("%i | %f | MI = %f\n", n, q.eta[n], q.mi[n]);
		ver++;
	}

	for (int n = 0; n < size; n++) {
		printf("ETA[%i] = %f - MI[%i] = %f - W[%i] = %f \n", n, q.eta[n], n, q.mi[n], n, q.w[n]);
		if (n == sizeQuad - 1 || n == 2 * sizeQuad - 1
				|| n == 3 * sizeQuad - 1) {
			printf("\n");
		}
	}

	desalocar1DDouble(W);
	desalocar1DDouble(q.w);
	desalocar1DDouble(MI);
	desalocar1DDouble(q.eta);
	desalocar1DInteger(Mapping);
	desalocar1DDouble(q.mi);
}

int* GetMapping(int N, int sizeQ) {
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

double* GetWforQuadrature(int N) {
	//DECLARA O PONTEIRO PARA O PESO ===============================
	double *W;
	//==============================================================

	//ALOCANDO E PREENCHENDO OS VETORES ============================
	switch (N) {
	case 2:
		W = alocar1DDouble(1);
		W[0] = 1;
		break;
	case 4:
		W = alocar1DDouble(1);
		W[0] = 0.3333333;
		break;
	case 6:
		W = alocar1DDouble(2);
		W[0] = 0.1761263;
		W[1] = 0.1572071;
		break;
	case 8:
		W = alocar1DDouble(3);
		W[0] = 0.1209877;
		W[1] = 0.0907407;
		W[2] = 0.0925926;
		break;
	}
//==============================================================

	return W;
}

double* GetMiforQuadrature(int N) {
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
//=================================================================
