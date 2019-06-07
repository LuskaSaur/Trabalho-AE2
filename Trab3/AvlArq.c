#include "./Lib/AvlArq.h"
#include <stdlib.h>
#include <string.h>
#define TAM 10

int max(int a, int b){
    if(a>b) return a;
    return b;
}

int altura(avl* atu){
    if(atu) return atu->altura;
    return -1;
}

avl* criaAvl(){
    return NULL;
}

avl* criaNo(void* comparador, int index, int tam){
    avl *a = (avl*)malloc(sizeof(avl));
    a->sad = a->sae = a->altura = 0;
    a->comparador = malloc(tam);
    memcpy(a->comparador, comparador, tam);//*a->comparador = *comparador;
    a->index = index;
    return a;
}

avl* Lrot(avl* k2){
    avl* k1 = k2->sae;
    k2->sae = k1->sad;
    k1->sad = k2;

    k2->altura = max(altura(k2->sae), altura(k2->sad)) + 1;
    k1->altura = max(altura(k1->sae), altura(k2)) + 1;
    return k1; /* new root */
}

avl* Rrot(avl* k1){
    avl* k2 = k1->sad;
    k1->sad = k2->sae;
    k2->sae = k1;

    k1->altura = max(altura(k1->sae), altura(k1->sad)) + 1;
    k2->altura = max(altura(k2->sad), altura(k1)) + 1;

    return k2;  /* New root */
}

avl* RLrot(avl* k3){
    k3->sae = Rrot(k3->sae);
    return Lrot(k3);
}

avl* LRrot(avl* k1){
    k1->sad = Lrot(k1->sad);
    return Rrot(k1);
}
avl* inseriravl(avl* atu, void* comparador, int index,int(*lessequal)(void*, void*),int tam){
    if(atu == NULL) 
        atu = criaNo(comparador, index,tam);
    else if(lessequal(comparador,atu->comparador)){
        atu->sae = inseriravl(atu->sae, comparador, index, lessequal,tam);
        if(altura(atu->sae) - altura(atu->sad) == 2){
            if(lessequal(comparador,atu->sae->comparador)) atu = Lrot(atu);
            else atu = RLrot(atu);
        }
    }
    else if(!lessequal(comparador,atu->comparador)){
        atu->sad = inseriravl(atu->sad, comparador, index,lessequal,tam);
        if(altura(atu->sad) - altura(atu->sae) == 2){
            if(!lessequal(comparador,atu->sad->comparador)) atu = Rrot(atu);
            else atu = LRrot(atu);
        }
    }
    atu->altura = max(altura(atu->sae), altura(atu->sad)) + 1;
    return atu;
}

avl* buscaavl(avl *a, void *comparador, int(*maior)(void*,void*), int(*menor)(void*,void*)){
    if(a == NULL)
        return NULL;
    else if(maior(comparador,a->comparador))
        a = buscaavl(a->sad,comparador,maior,menor);
    else if(menor(comparador,a->comparador))
        a = buscaavl(a->sae,comparador,maior,menor);
    return a;
}

void imprimeavl(avl *a, int val) {
    if(a!=NULL) {
        if(val==0) printf("%d\n",*(int*)a->comparador);
        imprimeavl(a->sae,val);
        if(val==1) printf("%d\n",*(int*)a->comparador);
        imprimeavl(a->sad,val);
        if(val==2) printf("%d\n",*(int*)a->comparador);
    }
}

avl* liberaavl(avl *a) {
    if(a != NULL) {
        liberaavl(a->sae);
        liberaavl(a->sad);
        free(a);
    }
    return NULL;
}
/*
int taEmOrdem(avl *atu){
    int res = 1;
    if(atu->sae) res &= (taEmOrdem(atu->sae) && atu->sae->id <= atu->id);
    if(atu->sad) res &= (taEmOrdem(atu->sad) && atu->sad->id >= atu->id);
    return res;
}
*/
int idElementos(avl *atu){
    int res = 0;
    if(atu) res = 1 + idElementos(atu->sae) + idElementos(atu->sad);
    return res;
}

int altura2(avl *atu){
    if(!atu) return 0;
    int res = 0;
    if(atu->sae) res += 1 + altura2(atu->sae);
    if(atu->sad) res=max(res, 1 + altura2(atu->sad));
    return res;
}

int taBalanceada(avl *atu){
    if(!atu) return 1;
    int bf = altura2(atu->sad) - altura2(atu->sae);
    if(bf>1 || bf<-1) return 0;
    return taBalanceada(atu->sae) && taBalanceada(atu->sad);
}

/*int taCerto(avl *atu, int n){
    return (taEmOrdem(atu) && idElementos(atu) == n && taBalanceada(atu));
}
*/
avl* PreencheArq(FILE *fp, avl *arv, char nome[][30], void *comparador, int(*lessequal)(void*, void*), int tam, int VetID[]){ 
    for(int i=0; i<TAM; i++){
        Produto tmp;
        tmp.id = i;
        VetID[i] = tmp.id;
        tmp.quantidade = i*i;
        tmp.modelo = 400*i + (1+i)*10 + i;
        tmp.custo = i*i/2.0;
        strcpy(tmp.nome, nome[i]);
        fwrite(&tmp, sizeof(Produto), 1,fp);
        arv = inseriravl(arv,comparador,tmp.id,lessequal,tam);
    }
    return arv;   
}

void BuscaArvArq(FILE *fp, avl *arv, void *comparador, int(*maior)(void*,void*), int(*menor)(void*,void*)){
    avl *result;
    Produto produtfinal;
    result = buscaavl(arv, comparador, maior, menor);
    if(!result){
        printf("Não achei saporra\n");
        return;
    }
    fseek(fp,0,SEEK_SET);
    fseek(fp,sizeof(Produto)*result->index,SEEK_SET);
    fread(&produtfinal,sizeof(Produto),1,fp);
    //MostraProduto(produtfinal);
}

//INTERVALOS DE BUSCA: <,>,<=,>=

void BuscaIntervalo(avl *arv, void* comparador, int(*intervalo)(void*, void*), int(*equal)(void*, void*)){
    if(arv == NULL)
        return;
    if(equal(comparador, arv->comparador)){
        if(arv->sae && intervalo(arv->comparador, comparador))
            BuscaIntervalo(arv->sae, comparador, intervalo, equal);
        //printf("%d\n", *(int*) arv->comparador);
        if(arv->sad && intervalo(arv->comparador, comparador))
            BuscaIntervalo(arv->sad, comparador, intervalo, equal);
    }
    else{
        if(arv->sae)
            BuscaIntervalo(arv->sae, comparador, intervalo, equal);
        if(intervalo(arv->comparador, comparador))
            //printf("%d\n", *(int*)arv->comparador);
        if(arv->sad)
            BuscaIntervalo(arv->sad, comparador, intervalo, equal);
    }
}