#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "./Lib/Arquivo.h"
#include "./Lib/Produto.h"
#include "./Lib/AvlArq.h"
#include "./Lib/Hash.h"
#define TAM 100000
//For compile this code: gcc -w Hash.c AvlArq.c Arquivo.c Produto.c main.c -o main

int main(){
	clock_t tempo1,tempo2;
	float media[5];
	FILE *fp;
	fp = fopen("Produtos", "w+b");
	int vetID[TAM];
	float vetCusto[TAM];

	//1 - Buscando em AVL para o atributo chave | OK
	printf("Arvore de AVL: \n");
	avl *ArvID;
	ArvID = criaAvl();
	GenerateProducts(fp, vetID, vetCusto);
	for(int i=0; i<TAM; i++)
		ArvID = inseriravl(ArvID, vetID+i, i, LessOrEqualAmountThan, sizeof(int));
	for(int i=0; i<TAM; i+=(TAM/30)){
		tempo1 = clock();
		BuscaArvArq(fp, ArvID, vetID+i, GreaterAmountThan, LessAmountThan);
		tempo2 = clock();
	}
	media[0] = ((double)(tempo2-tempo1)/(CLOCKS_PER_SEC/1000));
	printf("Tempo medio: %fms\n", 1000*media[0]/30);

	//2 - Usando Hashing para o atributo chave
	printf("HASH de ID: \n");
	hash* hashID;
	int count;
	hashID = criaHash(TAM);
	fseek(fp, 0, SEEK_SET);
	Produto aux;
	int index = 0;
	while(fread(&aux, sizeof(Produto), 1, fp) > 0 &&  !feof(fp)){
		insereHash_enderAberto(hashID, index, aux.id);
		index++;
	}
	fseek(fp, 0, SEEK_SET);
	index = 0;
	count = TAM/10;
	while(fread(&aux, sizeof(Produto), 1, fp) > 0 &&  !feof(fp) && count>0){
		insereHash_enderAberto(hashID, index, aux.id);//int buscaHash_enderAberto(hash* h, int id, FILE *fp, Produto key)
		index++;
		count--;
	}
	fseek(fp, 0, SEEK_SET);
	for(int i=0; i < TAM; i+=(TAM/30)){
		fread(&aux, sizeof(Produto), 1, fp);
		tempo1 = clock();
		buscaHash_enderAberto(hashID, fp, aux);
		tempo2 = clock();
	}
	media[1] = ((double)(tempo2-tempo1)/(CLOCKS_PER_SEC/1000));
	printf("Tempo medio: %fms\n", 1000*media[1]/30);
	printf("Numero de colisoes: %d\n", hashID->numCo);

	//3 - Busca sequencial no arquivo para o atributo chave
	printf("Busca sequencial em arquivo: \n");
	Produto *vetProd;
	int size = 0;
	for(int i=0; i<TAM; i+=(TAM/30)){
		tempo1 = clock();
		vetProd = SequentialConditionalSearchInFile(vetCusto+i, sizeof(Produto), fp, PEqualNameThan, &size);
		tempo2 = clock();
	}
	media[2] = ((double)(tempo2-tempo1)/(CLOCKS_PER_SEC/1000));
	printf("Tempo medio: %fms\n", 1000*media[2]/30);
	//MostraProduto(ans);

	//4 - Busca do tipo >, >=, < ou <= usando AVL para um atributo nao chave
	printf("Busca condicional na arvore: \n");
	avl *ArvCost;
	ArvCost = criaAvl();
	for(int i=0; i<TAM; i++)
		ArvCost = inseriravl(ArvCost, vetCusto+i, i, LessOrEqualCostThan, sizeof(float));
	for(int i=0; i<TAM; i+=(TAM/30)){
		tempo1 = clock();
		BuscaIntervalo(ArvCost, vetCusto+i, GreaterCostThan, EqualCostThan);
		tempo2 = clock();
	}
	media[3] = ((double)(tempo2-tempo1)/(CLOCKS_PER_SEC/1000));
	printf("Tempo medio: %fms\n", 1000*media[3]/30);

	//5 - Busca do tipo >, >=, < ou <= usando busca sequencial no arquivo para o mesmo atributo
	printf("Busca condicional sequencial: \n");
	size = 0;
	for(int i=0; i<TAM; i+=(TAM/30)){
		tempo1 = clock();
		vetProd = SequentialConditionalSearchInFile(vetCusto+i, sizeof(Produto), fp, PGreaterCostThan, &size);
		tempo2 = clock();
	}
	media[4] = ((double)(tempo2-tempo1)/(CLOCKS_PER_SEC/1000));
	printf("Tempo medio: %fms\n", 1000*media[4]/30);

	//<<Fim codigo>>
	liberaavl(ArvID);
	liberaavl(ArvCost);
	return 0;
}