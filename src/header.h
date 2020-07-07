//CRIADO POR MATHEUS RIBEIRO | 26/JUN/2020 ========================
//=================================================================
#ifndef HEADER_H_
#define HEADER_H_
//=================================================================
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <omp.h>
#include <cblas.h>
//=================================================================
typedef struct {
	double *mi;
	double *eta;
	double *w;
} quadratura;
//=================================================================
void FillingTheQuadratureStruct(int N);
   int* GetMapping(int N, int sizeQ);
double* GetWforQuadrature(int N);
double* GetMiforQuadrature(int N);
//=================================================================
double* alocar1DDouble(int tamanho);
   int* alocar1DInteger(int tamanho);
   void desalocar1DDouble(double *vetor);
   void desalocar1DInteger(int *vetor);
//=================================================================
#endif /* HEADER_H_ */
