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
void FillingTheQuadratureStruct(int N){
	 int    size = N * (N + 2) / 2;
	int* Mapping = GetMapping(size/4);
 double*       W = GetWforQuadrature(N);
 //double*      MI = GetMiforQuadrature(N);

	quadratura q;
	q.w  = alocar1DDouble(size);
	q.mi = alocar1DDouble(size);

	int sizeQuad = size / 4;
	for(int n = 0; n < sizeQuad; n++){
		q.w[n] = W[Mapping[n]];
		//=============================
		    q.w[n + sizeQuad] = q.w[n];
		q.w[n + 2 * sizeQuad] = q.w[n];
		q.w[n + 3 * sizeQuad] = q.w[n];
		//=============================
		printf("%i | W = %f \n", Mapping[n], q.w[n]);
	}

	desalocar1DDouble(W);
	desalocar1DInteger(Mapping);
}

int* GetMapping(int sizeQ) {
	int *map = alocar1DInteger(sizeQ);

	switch(sizeQ){
	case 6:
		map[0] = 0;
		map[1] = 1; map[3] = 1;
		map[2] = 0; map[4] = 1; map[5]= 0;
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
		Mi[3] = 0.9261808;
		break;
	}
	//==============================================================

	return Mi;
}
//=================================================================
