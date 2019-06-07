#include <stdio.h>
#ifndef TRAB3_H
#define TRAB3_H

typedef struct Produto{
	int id; 		//4	(CHAVE)
	int modelo;  	// 4
	float custo; 	// 4
	char nome[32];	// 32
	int quantidade; //4
}Produto;

int EqualProduct(Produto a, Produto b);

//Construct function
Produto create(int id, int mdl, float c, char n[], int qtd);

//Generate 10 Products
void GenerateProducts(FILE *fp, int vetID[], float vetCusto[]);

//Print the product
void MostraProduto(Produto current);

//Comparatives of Cost
int EqualCostThan(float* pCost, float* cost);
int LessCostThan(float* pCost, float *cost);
int LessOrEqualCostThan(float* pCost, float *cost);
int GreaterCostThan(float* pCost, float *cost);
int GreaterOrEqualCostThan(float* pCost, float* cost);

//Comparatives of Names
int EqualNameThan(char* pName, char* name);
int LessNameThan(char* pName, char* name);
int LessOrEqualNameThan(char* pName, char* name);
int GreaterNameThan(char* pName, char* name);
int GreaterOrEqualNameThan(char* pName, char* name);

//Amount of product
int EqualAmountThan(int* pAmount, int* amount);
int LessAmountThan(int* pAmount, int* amount);
int LessOrEqualAmountThan(int* pAmount, int* amount);
int GreaterAmountThan(int* pAmount, int* amount);
int GreaterOrEqualAmountThan(int* pAmount, int* amount);

//Compare product and amount
int PGreaterOrEqualAmountThan(Produto* p, int* amount);
int PGreaterAmountThan(Produto* p, int* amount);
int PLessAmountThan(Produto* p, int* amount);
int PLessOrEqualAmountThan(Produto* p, int* amount);
int PEqualAmountThan(Produto* p, int* amount);

//Compare product and cost
int PGreaterOrEqualCostThan(Produto* p, float* cost);
int PGreaterCostThan(Produto* p, float* cost);
int PLessCostThan(Produto* p, float* cost);
int PLessOrEqualCostThan(Produto* p, float* cost);
int PEqualCostThan(Produto* p, float* cost);

//Compare product and name
int PGreaterOrEqualNameThan(Produto* p, char* name);
int PGreaterNameThan(Produto* p, char* name);
int PLessNameThan(Produto* p, char* name);
int PLessOrEqualNameThan(Produto* p, char* name);
int PEqualNameThan(Produto* p, char* name);

#endif

