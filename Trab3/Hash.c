#include <stdio.h>
#include <stdlib.h>
#include "./Lib/Hash.h"


hash* criaHash(int tableSize){
    hash* h = (hash*) malloc(sizeof(hash));
    if(h != NULL){
        h->tableSize = tableSize;
        h->item = (int**) malloc((tableSize + tableSize/10) * sizeof(int**));
        if(h->item ==  NULL){
            free(h);
            return NULL;
        }
        h->qtd = h->numCo = 0;
        for(int i=0; i < (h->tableSize + tableSize/10); i++)
            h->item[i] = NULL;
    }
  return h;
}

void liberaHash(hash* h){
    if(h != NULL){
        for(int i = 0; i < (h->tableSize);i++)
            if(h->item[i] != NULL)
                free(h->item[i]);
        free(h->item);
        free(h);
    }
}

int chaveDivisao(int chave, int tableSize){
  return chave%tableSize;
}

/*int chaveMultiplica(int chave, int tableSize){
  float a = 0.618033898;
  float val = chave*a;
  val = val - (int)val;
  return (int) (tableSize*val);
}*/


/*int sondagemLinear(int pos,int i, int tableSize){
  return (pos + i)%tableSize;
}*/

/*int contaColisao(hash* h){
  return h->numCo++;
}*/

int insereHash_enderAberto(hash* h, int index, int id){
    if(h == NULL)
        return 0;
    int newPos = newPos = chaveDivisao(id, h->tableSize), pos;
    pos = newPos;
    //printf("%d\n", newPos);
    for(int i=0;i<h->tableSize;i++){
        if(h->item[newPos]){
            newPos = TratamentoPorOverflow(newPos, h->tableSize, h);
            h->numCo++;
        }
        if(!h->item[newPos]){
            int *new;
            new = (int*)malloc(sizeof(int*));
            if(new == NULL)
                return 0;
            *new = index;
            h->item[newPos] = new;
            h->qtd++;
            return 1;
        }
    }
    return 0;
}

int TratamentoPorOverflow(int pos, int tableSize, hash *h){
  return tableSize + h->numCo;
}


int buscaHash_enderAberto(hash* h, FILE *fp, Produto key){
    if(h == NULL)
        return 0;
    int newPos = chaveDivisao(key.id, h->tableSize);
    if(h->item[newPos] == NULL)
        return 0;
    else{
        Produto produtfinal;
        int result = *h->item[newPos];
        fseek(fp,sizeof(Produto)*result,SEEK_SET);
        fread(&produtfinal,sizeof(Produto),1,fp);
        if(EqualProduct(produtfinal, key))
            return 1;
        for(int i=h->tableSize; i<h->tableSize+h->tableSize/10; i++){
            int result = *h->item[newPos];
            fseek(fp,sizeof(Produto)*result,SEEK_SET);
            fread(&produtfinal,sizeof(Produto),1,fp);
            if(EqualProduct(produtfinal, key))
                return 1;
        }
        return 0;

    }
    newPos = TratamentoPorOverflow(newPos,h->tableSize, h);
    return 0;
}