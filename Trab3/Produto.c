#include "./Lib/Produto.h"
#include <stdio.h>
#include <string.h>
#include "./Lib/Hash.h"

Produto create(int id, int mdl, float c, char n[], int qtd){
	Produto tmp;
	tmp.id = id;
	tmp.modelo = mdl;
	tmp.custo = c;
	strcpy(tmp.nome, n);
	tmp.quantidade = qtd;
	return tmp;
}

int EqualProduct(Produto a, Produto b){
	if(b.id == a.id && a.modelo == b.modelo && a.custo == b.custo && strcmp(a.nome,b.nome) ==0 && a.quantidade == b.quantidade)
		return 1;
	return 0;
}

void * GenerateString(char nome[30]){
    for(int i =0;i<30;i++){
        nome[i] = 'A' + rand()%26;
    }
}

void GenerateProducts(FILE *fp, int vetID[], float vetCusto[]){
	char nome[30];
	int ant = 1;
    for(int i=0; i<100000; i++){
    	Produto tmp;
      	tmp.id = i;
      	ant = tmp.id;
      	//printf("%d = %d\n", i, tmp.id);
        vetID[i] = tmp.id;
      	tmp.quantidade = rand()%1000;
      	tmp.modelo = 400*i + (1+i)*10 + i;
      	tmp.custo = rand()%100000;
        vetCusto[i] = tmp.custo;
        GenerateString(nome);
      	strcpy(tmp.nome,nome);
      	fwrite(&tmp, sizeof(Produto), 1,fp);
    }
}

void MostraProduto(Produto current){
	printf("Id = %d Modelo = %d Custo = %.2f Nome = %s Quantidade = %d\n", current.id, current.modelo, current.custo, current.nome, current.quantidade);
}

int EqualCostThan(float* pCost, float* cost){
	if(*pCost == *cost)
		return 1;
	return 0;
}

int LessCostThan(float* pCost, float *cost){
	if(*pCost < *cost)
		return 1;
	return 0;
}

int LessOrEqualCostThan(float* pCost, float *cost){
	if(*pCost <= *cost)
		return 1;
	return 0;
}

int GreaterCostThan(float* pCost, float *cost){
	if(*pCost > *cost)
		return 1;
	return 0;
}

int GreaterOrEqualCostThan(float* pCost, float* cost){
	if(*pCost >= *cost)
		return 1;
	return 0;
}

int EqualNameThan(char* pName, char* name){
	if(strcmp(pName, name) == 0)
		return 1;
	return 0;
}

int LessNameThan(char* pName, char* name){
	if(strcmp(pName, name) < 0)
		return 1;
	return 0;
}

int LessOrEqualNameThan(char* pName, char* name){
	if(strcmp(pName, name) <= 0)
		return 1;
	return 0;
}

int GreaterNameThan(char* pName, char* name){
	if(strcmp(pName, name) > 0)
		return 1;
	return 0;
}

int GreaterOrEqualNameThan(char* pName, char* name){
	if(strcmp(pName, name) >= 0)
		return 1;
	return 0;
}

int EqualAmountThan(int* pAmount, int* amount){
	if(*pAmount == *amount)
		return 1;
	return 0;
}

int LessAmountThan(int* pAmount, int* amount){
	if(*pAmount < *amount)
		return 1;
	return 0;
}

int LessOrEqualAmountThan(int* pAmount, int* amount){
	if(*pAmount <= *amount)
		return 1;
	return 0;
}

int GreaterAmountThan(int* pAmount, int* amount){
	if(*pAmount > *amount)
		return 1;
	return 0;
}

int GreaterOrEqualAmountThan(int* pAmount, int* amount){
	if(*pAmount >= *amount)
		return 1;
	return 0;
}
//-------------------------------------------------------

int PGreaterOrEqualAmountThan(Produto* p, int* amount){
	if(p->quantidade >= *amount)
		return 1;
	return 0;
}

int PGreaterAmountThan(Produto* p, int* amount){
	if(p->quantidade > *amount)
		return 1;
	return 0;
}

int PLessAmountThan(Produto* p, int* amount){
	if(p->quantidade < *amount)
		return 1;
	return 0;
}

int PLessOrEqualAmountThan(Produto* p, int* amount){
	if(p->quantidade <= *amount)
		return 1;
	return 0;
}

int PEqualAmountThan(Produto* p, int* amount){
	if(p->quantidade == *amount)
		return 1;
	return 0;
}

int PGreaterOrEqualCostThan(Produto* p, float* cost){
	if(p->custo >= *cost)
		return 1;
	return 0;
}

int PGreaterCostThan(Produto* p, float* cost){
	if(p->custo > *cost)
		return 1;
	return 0;
}

int PLessCostThan(Produto* p, float* cost){
	if(p->custo < *cost)
		return 1;
	return 0;
}

int PLessOrEqualCostThan(Produto* p, float* cost){
	if(p->custo <= *cost)
		return 1;
	return 0;
}

int PEqualCostThan(Produto* p, float* cost){
	if(p->custo == *cost)
		return 1;
	return 0;
}

int PGreaterOrEqualNameThan(Produto* p, char* name){
	if(strcmp(p->nome, name) >= 0)
		return 1;
	return 0;
}

int PGreaterNameThan(Produto* p, char* name){
	if(strcmp(p->nome, name) > 0)
		return 1;
	return 0;
}

int PLessNameThan(Produto* p, char* name){
	if(strcmp(p->nome, name) < 0)
		return 1;
	return 0;
}

int PLessOrEqualNameThan(Produto* p, char* name){
	if(strcmp(p->nome, name) <= 0)
		return 1;
	return 0;
}

int PEqualNameThan(Produto* p, char* name){
	if(strcmp(p->nome, name) == 0)
		return 1;
	return 0;
}