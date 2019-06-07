#include "Produto.h"
#include <stdio.h>
#ifndef HASH_H
#define HASH_H

typedef struct hash{
  	int tableSize, numCo, qtd;
  	int **item;
}hash;

hash* criaHash(int tableSize); //cria tabela hash | OK
void liberaHash(hash* h); //esvazia tabela e destroi | OK
int chaveDivisao(int chave, int tableSize); //calculo da insercao do produto na tabela | OK
int insereHash_enderAberto(hash* h, int index, int id); //insere produto colisao | OK
int buscaHash_enderAberto(hash* h, FILE *fp, Produto key); //busca produto colisao | Ok
//int sondagemLinear(int pos,int i, int tableSize); //sondagem linear para colisa 
//int chaveMultiplica(int chave, int tableSize); //outro metodo do calculo da insercao
//int contaColisao(hash* h); //conta as colisoes

#endif