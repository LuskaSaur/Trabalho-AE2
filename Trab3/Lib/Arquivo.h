#include <stdio.h>
#ifndef ARQUIVO_H
#define ARQUIVO_H

//Return the number of elements in file
int AmountOfElementsInFile(int sizeOfType, FILE *fp);

//Return the element that obey the condition Equal
void* SequentialSearchInFile(void* key, int typeSize, FILE *fp, int(*equal)(void*, void*));

//Return an array with elements that obey the condition cmp
void* SequentialConditionalSearchInFile(void* key, int typeSize, FILE *fp, int (*cmp)(void*, void*), int *size);

#endif