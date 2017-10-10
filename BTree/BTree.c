//
//  BTree.c
//
//
//  Created by Larissa Cristina on 23/08/17.
//
//
#include "BTree.h"
#include <stdlib.h>
#include <stdio.h>

struct BinaryTree{
    int info;
    struct BinaryTree *esq;
    struct BinaryTree *dir;
};

typedef struct BinaryTree TBinaryTree;

void insertBinary(TBinaryTree** T, int info)
{
    if(*T == NULL)
    {
        *T = (TBinaryTree*)malloc(sizeof(TBinaryTree));
        (*T)->esq = NULL;
        (*T)->dir = NULL;
        (*T)->info = info;
    }
    else
    {
        if((*T)->info >= info)
        {
            insertBinary(&((*T)->esq), info);
        }
        else
        {
            insertBinary(&((*T)->dir), info);
        }
    }
}

TBinaryTree *search(TBinaryTree* T, int info, TBinaryTree** Pai){
    if(T != NULL){
        if(T->info == info){
            return T;
        }
        else{
            *Pai = T;
            if(T->info > info){
                return search(T->esq, info, Pai);
            }
            else{
                return search(T->dir, info, Pai);
            }
        }
    }
    return NULL;
}

//primeiro
void preOrdem(TBinaryTree *T)
{
    if(T != NULL)
    {
        printf("%d \n", T->info);
        preOrdem(T->esq);
        preOrdem(T->dir);
    }
}

//primeiro
void preOrdemNivel(TBinaryTree *T, int nivel)
{
    if(T != NULL)
    {
        printf("%d, ", T->info);
        printf("Nivel: %d \n", nivel);
        nivel++;
        preOrdemNivel(T->esq, nivel);
        preOrdemNivel(T->dir, nivel);
    }
}

//primeiro
int preOrdemFolhas(TBinaryTree *T){
    if(T == NULL){
        return 0;
    }else{
        if (T->esq == NULL && T->dir == NULL) {
            return 1;
        }
        return preOrdemFolhas(T->esq) + preOrdemFolhas(T->dir);
    }
}

//primeiro
int preOrdemNosInternos(TBinaryTree *T){
    if(T == NULL){
        return 0;
    }else{
        if (T->esq != NULL || T->dir != NULL) {
            return 1;
        }
        return preOrdemNosInternos(T->esq) + preOrdemNosInternos(T->dir);
    }
}

//primeiro
int preOrdemNos(TBinaryTree *T){
    if(T == NULL){
        return 0;
    }else{
        if (T->esq != NULL || T->dir != NULL) {
            return 1;
        }
        return preOrdemNos(T->esq) + preOrdemNos(T->dir);
    }
}

//primeiro
int contarFilhos(TBinaryTree *T){
    if(T == NULL){
        return 0;
    }else{
        if (T->esq != NULL || T->dir != NULL) {
            return 1;
        }
        return preOrdemNos(T->esq) + preOrdemNos(T->dir);
    }
}

//primeiro
int numeroFilhos(TBinaryTree *T){
    if(T == NULL){
        return 0;
    }else{
        if (T->esq != NULL || T->dir != NULL) {
            return 1;
        }
        return preOrdemNos(T->esq) + preOrdemNos(T->dir);
    }
}

//meio
void ordemSimetrica(TBinaryTree *T)
{
    if (T!= NULL)
    {
        ordemSimetrica(T->esq);
        printf("%d \n",T->info);
        ordemSimetrica(T->dir);
    }
}

//fim
void posOrdem(TBinaryTree *T)
{
    if(T!=NULL)
    {
        posOrdem(T->esq);
        posOrdem(T->dir);
        printf("%d \n", T->info);
    }
}

//minimo
TBinaryTree *min(TBinaryTree *T){
    if(T==NULL){
        return NULL;
    }
    if (T->esq == NULL) {
        return T;
    }
    return min(T->esq);
}

//maximo
TBinaryTree *max(TBinaryTree *T){
    if(T==NULL){
        return NULL;
    }
    if (T->dir == NULL) {
        return T;
    }
    return max(T->dir);
}

//remoção nó folha(só deleta)
void removeBinaryTree(TBinaryTree *T, int info){
    TBinaryTree *Pai;
    TBinaryTree *AUX = search(T, info, &Pai);
    TBinaryTree *tmp;
    
    if(AUX!=NULL){
        if(AUX->dir==NULL && AUX->esq==NULL){//folha
            if (Pai->esq==AUX) {
                Pai->esq = NULL;
            }else{
                Pai->dir = NULL;
            }
            free(AUX);
        }else if((AUX->dir==NULL && AUX->esq!=NULL) || (AUX->dir!=NULL && AUX->esq==NULL)){//um filho
            tmp = (AUX->dir!=NULL ? AUX->dir : AUX->esq);
            if (Pai->esq==AUX) {
                Pai->esq = tmp;
            }else{
                Pai->dir = tmp;
            }
            free(tmp);
        }else{//dois filhos
            TBinaryTree *tmp2 = max(AUX->esq);
            if (Pai->esq==AUX) {
                Pai->esq = tmp2;
            }else{
                Pai->dir = tmp2;
            }
            if(AUX->esq->dir!=NULL){
                TBinaryTree *tmp3 = AUX->esq;
                tmp3->dir = tmp2->esq;
                tmp2->esq = tmp3;
                tmp2->dir = AUX->dir;
            }else{
                tmp2->dir = AUX->dir;
            }
            free(AUX);
        }
    }
}

//remoçao com dois filhos ( < a direita ou > a esquerda)

int main()
{
    TBinaryTree *T = NULL;
    
    /*insertBinary(&T, 45);
    insertBinary(&T, 39);
    insertBinary(&T, 60);
    insertBinary(&T, 23);
    insertBinary(&T, 42);
    insertBinary(&T, 55);
    insertBinary(&T, 79);
    insertBinary(&T, 10);
    insertBinary(&T, 34);
    insertBinary(&T, 44);
    insertBinary(&T, 77);
    insertBinary(&T, 83);
    insertBinary(&T, 29);*/
    
    insertBinary(&T, 39);
    insertBinary(&T, 60);
    insertBinary(&T, 23);
    insertBinary(&T, 42);
    insertBinary(&T, 55);
    insertBinary(&T, 79);
    insertBinary(&T, 10);
    insertBinary(&T, 34);
    insertBinary(&T, 44);
    
    //search(T, 3);
    
    preOrdem(T);
    
    //printf("Quantidade de Folhas: %d \n",preOrdemFolhas(T));
    
    printf("Vamos remover \n");
    
    //printf("Quantidade de Nos Internos: %d \n",preOrdemNosInternos(T));
    
    removeBinaryTree(T, 39);
    
    preOrdem(T);
    return 0;
}
