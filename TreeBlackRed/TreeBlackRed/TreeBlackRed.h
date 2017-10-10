//
//  TreeBlackRed.h
//  TreeBlackRed
//
//  Created by Larissa Cristina on 04/10/17.
//  Copyright © 2017 Larissa Cristina. All rights reserved.
//

#ifndef TreeBlackRed_h
#define TreeBlackRed_h

#include<stdio.h>
#include<stdlib.h>
#define RED 1
#define BLACK 0


struct NO{
    int info;
    struct NO *esq, *dir;
    int cor;
};

typedef struct NO TreeBlackRed;

int cor(TreeBlackRed* H);
void trocaCor(TreeBlackRed** H);
TreeBlackRed* rotacionaEsquerda(TreeBlackRed** A);
TreeBlackRed* rotacionaDireita(TreeBlackRed** A);
TreeBlackRed* duoEsqRED(TreeBlackRed** H);
TreeBlackRed* duoDirRED(TreeBlackRed** H);
TreeBlackRed* balancear (TreeBlackRed** H);
void insereNO(TreeBlackRed** H, int info, int *resp);
int insere_TreeBlackRed(TreeBlackRed** T,int info);
void preOrdem(TreeBlackRed *T);
TreeBlackRed* inicializa_TreeBlackRed();
TreeBlackRed* removerMenor(TreeBlackRed** H);
TreeBlackRed* procurarMenor(TreeBlackRed* atual);
int consulta_TreeBlackRed(TreeBlackRed* T, int info);
int remove_TreeBlackRed(TreeBlackRed** T, int info);
TreeBlackRed* removeNO(TreeBlackRed** H, int info);
#endif /* TreeBlackRed_h */
