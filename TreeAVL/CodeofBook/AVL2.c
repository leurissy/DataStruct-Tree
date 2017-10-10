//
//  AVL2.c
//  TreeAVL
//
//  Created by Larissa Cristina on 03/10/17.
//  Copyright © 2017 Larissa Cristina. All rights reserved.
//

#include "AVL2.h"
//direita
void caso1(TreeAVL **pt, int h){
    TreeAVL *ptu, *ptv;
    ptu = (*pt) -> left;
    if(ptu->fb == -1){
        (*pt)->left = ptu->right;
        ptu->right = (*pt);
        (*pt)->fb = 0;
        (*pt) = ptu;
    }else{
        ptv = ptu->right;
        ptu->right = ptv->left;
        ptv -> left = ptu;
        (*pt)->left = ptv->right;
        ptv->right = (*pt);
        
        (*pt)->fb = (ptv->fb == -1) ? 1 : 0;
        ptu->fb = (ptv->fb == 1) ? -1 : 0;
        
        (*pt) = ptv;
    }
    (*pt)->fb = 0;
    h = 0;
}
//esquerda
void caso2(TreeAVL **pt, int h){
    TreeAVL *ptu, *ptv;
    ptu = (*pt) -> right;
    if(ptu->fb == 1){
        (*pt)->right = ptu->left;
        ptu->left = (*pt);
        (*pt)->fb = 0;
        (*pt) = ptu;
    }else{
        ptv = ptu->left;
        ptu->left = ptv->right;
        ptv -> right = ptu;
        (*pt)->right = ptv->left;
        ptv->left = (*pt);
        
        (*pt)->fb = (ptv->fb == 1) ? -1 : 0;
        ptu->fb = (ptv->fb == -1) ? 1 : 0;
        
        (*pt) = ptv;
    }
    (*pt)->fb = 0;
    h = 0;
}

void insertAVL(TreeAVL **pt, int info, int h){
    if((*pt)==NULL){
        *pt = (TreeAVL*)malloc(sizeof(TreeAVL));
        (*pt)->left = NULL;
        (*pt)->right = NULL;
        (*pt)->info = info;
        (*pt)->fb = 0;
        h = 1;
    }else{
        if (info < (*pt)->info) {
            insertAVL(&((*pt)->left), info, h);
            if(h){
                switch ((*pt)->fb) {
                    case 1:
                        (*pt)->fb = 0;
                        h = 0;
                        break;
                    case 0:
                        (*pt)->fb = -1;
                        break;
                    case -1:
                        caso1(pt, h);
                        break;
                }
            }
        }else{
            insertAVL(&((*pt)->right), info, h);
            if(h){
                switch ((*pt)->fb) {
                    case -1:
                        (*pt)->fb = 0;
                        h = 0;
                        break;
                    case 0:
                        (*pt)->fb = 1;
                        break;
                    case 1:
                        caso2(pt, h);
                        break;
                }
            }
        }
    }
}

//primeiro
void preOrdem(TreeAVL *T){
    if(T != NULL){
        printf("%d\n",T->info);
        preOrdem(T->left);
        preOrdem(T->right);
    }
}

//primeiro
void preOrdemNivel(TreeAVL *T, int nivel)
{
    if(T != NULL)
    {
        printf("%d, ", T->info);
        printf("Nivel: %d \n", nivel);
        nivel++;
        preOrdemNivel(T->left, nivel);
        preOrdemNivel(T->right, nivel);
    }
}

//meio
void ordemSimetrica(TreeAVL *T){
    if (T!= NULL){
        ordemSimetrica(T->left);
        printf("%d \n",T->info);
        ordemSimetrica(T->right);
    }
}


int main() {
    printf("TreeAVL\n");
    TreeAVL *T = NULL;
    
    insertAVL(&T,4,1);
    insertAVL(&T,2,1);
    insertAVL(&T,6,1);
    insertAVL(&T,1,1);
    insertAVL(&T,3,1);
    //preOrdem(T);
    insertAVL(&T,5,1);
    
    insertAVL(&T,7,0);
    insertAVL(&T,15,0);
    insertAVL(&T,15,0);
    puts("simetrica:");
    ordemSimetrica(T);
    
    
    printf("/nRaiz: %d \n", T->info);
    return 0;
}
