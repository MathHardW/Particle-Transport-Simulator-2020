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
	double *W = GetWforQuadrature(N);
	double *MI = GetMiforQuadrature(N);

	quadratura q;
	q.w = alocar1DDouble(size);
	q.mi = alocar1DDouble(size);
	q.n = alocar1DInteger(size);

	int sizeQuad = size / 4;                      //10
	int colSize = N / 2;                         //4
	int ver = 0;
	int x = 0;

	for (int n = 0; n < sizeQuad; n++) {
		printf("%i ", Mapping[n]);
	}

	//n ============================================================
	for (int n = 0; n < sizeQuad; n++) {
		if (ver >= colSize) {
			x++;
			colSize--;
			ver = 0;
		}
		//=============================
		q.n[n] = x;
		//=============================
		q.n[n + sizeQuad] = q.n[n];
		q.n[n + 2 * sizeQuad] = q.n[n];
		q.n[n + 3 * sizeQuad] = q.n[n];
		//=============================
		ver++;

	}

	printf("\n\n");

	//PESO =========================================================
	for (int n = 0; n < sizeQuad; n++) {
		q.w[n] = W[Mapping[n]];
		//=============================
		q.w[n + sizeQuad] = q.w[n];
		q.w[n + 2 * sizeQuad] = q.w[n];
		q.w[n + 3 * sizeQuad] = q.w[n];
		//=============================
		printf("%i | %i | W = %f \n", n, Mapping[n], q.w[n]);
	}

	printf("\n\n");

	//MI ==============================================================
	ver = 0;
	colSize = sizeQuad / 2;
	for (int n = 0; n < sizeQuad; n++) {
		if (ver >= colSize) {
			colSize--;
			ver = 0;
		}
		//=============================
		q.mi[n] = MI[ver]; //  mi[0] = MI[0]
		//=============================
		q.mi[n + sizeQuad] = q.mi[n];
		q.mi[n + 2 * sizeQuad] = q.mi[n];
		q.mi[n + 3 * sizeQuad] = q.mi[n];
		//=============================
		printf("%i | %i | MI = %f \n", n, q.n[n], q.mi[n]);
		ver++;
	}

	desalocar1DDouble(W);
	desalocar1DInteger(Mapping);
}

int* GetMapping(int N, int sizeQ) {
	int *map = alocar1DInteger(sizeQ);

	switch (N) {
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
