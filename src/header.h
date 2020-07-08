//CRIADO POR MATHEUS RIBEIRO | 26/JUN/2020 =====
//==============================================
#ifndef HEADER_H_
#define HEADER_H_
//HEADERS ======================================
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <omp.h>
#include <cblas.h>
//==============================================

//STRUCT'S =====================================
typedef struct {
	int numMat;	//numero de materias
	int numReg;	//numero de regioes
	int numGrp;	//numero de grupos

	double **matMaterial; //matriz dos materiais
	double **sigTotal; // matriz sigma total
	double **sigfic; //matriz sigma fiçao
	double **sigEsp; //matriz sigma espalhamento

	double material;
} DadosEntrada;

typedef struct {
	double *mi;
	double *eta;
	double *w;
} quadratura;
//==============================================

//MAIN FUNCTION ================================
void FillingTheQuadratureStruct(int N);
//==============================================

//BASE VECTOR'S ================================
int* GetMappingBase(int N, int sizeQ);
double* GetMiBase(int N);
//==============================================

//FULL VECTOR'S ================================
double* GetEtaFullVector(int N);
double* GetWFullVector(int N);
double* GetMiFullVector(int N);
//==============================================

//ALLOCATIONS ==================================
double* alocar1DDouble(int tamanho);
int* alocar1DInteger(int tamanho);
void desalocar1DDouble(double *vetor);
void desalocar1DInteger(int *vetor);
//==============================================
#endif /* HEADER_H_ */
