#include "AdptArray.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct AdptArray_
{
	int ArrSize;
	PElement* pElemArr;
	DEL_FUNC delFunc;
	COPY_FUNC copyFunc;
	PRINT_FUNC printFunc;
}AdptArray;

PAdptArray CreateAdptArray(COPY_FUNC copyFunc, DEL_FUNC delFunc,PRINT_FUNC printFunc)
{
	PAdptArray pArr = (PAdptArray)malloc(sizeof(AdptArray));
	if (pArr == NULL)
		return NULL;
	pArr->ArrSize = 0;
	pArr->pElemArr = NULL;
	pArr->delFunc = delFunc;
	pArr->copyFunc = copyFunc;
	pArr->printFunc = printFunc;
	return pArr;
}

Result SetAdptArrayAt(PAdptArray pArr, int idx, PElement pNewElem)
{
    PElement* newpElemArr;

    if (pArr == NULL) return FAIL;
    if (idx < 0) return FAIL;

    if (idx >= pArr->ArrSize)
    {
        // Extend Array

        newpElemArr = (PElement*) calloc((idx + 1), sizeof(*newpElemArr));
        if (newpElemArr == NULL) {
            return FAIL;
        }
        memcpy(newpElemArr, pArr->pElemArr, (pArr->ArrSize) * sizeof(*pArr->pElemArr));
        free(pArr->pElemArr);
        pArr->pElemArr = newpElemArr;
        pArr->ArrSize = idx + 1;
    }

    // Delete Previous Elem
    if (pArr->pElemArr[idx] != NULL) {
        pArr->delFunc(pArr->pElemArr[idx]);
    }
    pArr->pElemArr[idx] = pArr->copyFunc(pNewElem);

    return SUCCESS;
}



PElement GetAdptArrayAt(PAdptArray pArr, int index){
	if (pArr == NULL || pArr->pElemArr == NULL || index < 0 || index >= pArr->ArrSize) {
        return NULL;
    }
    PElement pElem = pArr->pElemArr[index];
    if (pElem == NULL || pArr->copyFunc == NULL) {
        return pElem;
    }
    PElement pElemCopy = pArr->copyFunc(pElem);
    return pElemCopy;

}

int GetAdptArraySize(PAdptArray pArr){
	if(pArr == NULL) return -1;
	return pArr->ArrSize;
}


void DeleteAdptArray(PAdptArray pArr)
{
	int i;
	if (pArr == NULL)
		return;
	for(i = 0; i < pArr->ArrSize; ++i)
	{
		if((pArr->pElemArr)[i] != NULL) {
			pArr->delFunc((pArr->pElemArr)[i]);
		}
		
	}
	free(pArr->pElemArr);
	free(pArr);
}

void PrintDB(PAdptArray pArr){
	if(pArr != NULL){
		for(int i = 0; i < pArr->ArrSize; i++){
			if((pArr->pElemArr)[i] != NULL) {
				pArr->printFunc((pArr->pElemArr)[i]);
			}
		}
	}
}