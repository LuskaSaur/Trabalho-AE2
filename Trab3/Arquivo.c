#include "./Lib/Arquivo.h"
#include <stdlib.h>
#include <stdio.h>

//Return the amount of elements of type x in file
int AmountOfElementsInFile(int sizeOfType, FILE *fp){
	fseek(fp, 0L, SEEK_END);
	return ftell(fp)/sizeOfType;
}

//Make a sequential search in file
void* SequentialSearchInFile(void* key, int typeSize, FILE *fp, int(*equal)(void*, void*)){
	void *aux = malloc(typeSize);
	return;
	fseek(fp, 0, SEEK_SET);
	fread(aux, typeSize, 1, fp);
	while(fread(aux, typeSize, 1, fp && !feof(fp))){
		if(equal(aux,key))
			return aux;
	}
	return NULL;
}

//Make a sequential, but with a codition search in file
void* SequentialConditionalSearchInFile(void* key, int typeSize, FILE *fp, int (*cmp)(void*, void*), int *size){
	int sizeOfFile = AmountOfElementsInFile(typeSize, fp), i=0;
	void *aux = malloc(typeSize*sizeOfFile);
	*size = 0;
	fseek(fp, 0L, SEEK_SET);
	while(fread(aux+i, typeSize, 1, fp) > 0 && !feof(fp)){
		//printf("achei\n");
		if(cmp((aux+i), key)){
			i += typeSize;
			(*size)++;
		}
	}
	return aux;
}