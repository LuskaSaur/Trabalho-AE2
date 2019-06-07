#include<stdio.h>
#include<stdlib.h>
#include "Produto.h"

typedef struct avl{
  void* comparador;
  int index,altura;
  struct avl* sae;
  struct avl* sad;
  struct avl* pai;
}avl;


avl* criaAvl();

avl* criaNo(void* comparador, int index, int tam);

int taCerto(avl *atu, int n);

avl* inseriravl(avl* atu, void* comparador, int index,int(*lessequal)(void*, void*),int tam);

void imprimeAvl(avl *a, int val,int(*lessequal)(void*, void*));

avl* buscaavl(avl *a, void *comparador, int(*maior)(void*,void*), int(*menor)(void*,void*));

avl* liberaavl(avl *a);

int taBalanceada(avl *atu);

void BuscaArvArq(FILE *fp, avl *arv, void *comparador, int(*maior)(void*,void*), int(*menor)(void*,void*));

avl* PreencheArq(FILE *fp, avl *arv, char nome[][30], void *comparador, int(*lessequal)(void*, void*), int tam, int VetID[]);

// BUSCA POR INTERVALO
void BuscaIntervalo(avl *arv, void* comparador, int(*intervalo)(void*, void*), int(*equal)(void*, void*));
//void BuscaIntervalo(FILE *fp, avl *arv, void* comparador, int(*intervalo)(void*,void*));