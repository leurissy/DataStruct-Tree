//
//  AVLTree.c
//  AED II
//
//  Created by Larissa Cristina on 20/09/17.
//  Copyright © 2017 Larissa Cristina. All rights reserved.
//

#include "AVLTree.h"

void insertAVL(TreeAVL** T, int info, int *H){
    if(*T == NULL){
        *T = (TreeAVL*)malloc(sizeof(TreeAVL));
        (*T)->left = NULL;
        (*T)->right = NULL;
        (*T)->info = info;
        (*T)->fb = 0;
        *H = 1;
    }else{
        if(info < (*T)->info){
            insertAVL(&((*T)->left), info, H);
            if(*H){
                switch ((*T)->fb) {
                    case 1:
                        (*T)->fb = 0;
                        *H = 0;
                        break;
                    case 0:
                        (*T)->fb = -1;
                        //H = 0;
                        break;
                    case -1:
                        caso1(T, H);
                        //H = 0;
                        break;
                }
            }
        }else{
            insertAVL(&((*T)->right), info, H);
            if(H){
                switch ((*T)->fb) {
                    case -1:
                        (*T)->fb = 0;
                        *H = 0;
                        break;
                    case 0:
                        (*T)->fb = 1;
                        break;
                    case 1:
                        caso2(T, H);
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

void rotationLeft(TreeAVL **T){
    TreeAVL * U;
    
    U = (*T) -> right;
    (*T) -> right = U -> left;
    U -> left = *T;
    (*T) -> fb = 0;
    *T = U;
}

void rotationRight(TreeAVL **T){
    TreeAVL * U;
    
    U = (*T) -> left;
    (*T) -> left = U -> right;
    U -> right = *T;
    (*T) -> fb = 0;
    *T = U;
}

void rotationDuoLeft(TreeAVL **T){
    TreeAVL *U, *V;
    
    U = (*T) -> right;
    V = U -> left;
    
    U -> left = V -> right;
    V -> right = U;
    (*T) -> right = V -> left;
    V -> left = (*T);
    
    (*T)->fb = (V->fb == 1) ? -1 : 0;
    U->fb = (V->fb == -1) ? 1 : 0;
    
    *T = V;
}

void rotationDuoRight(TreeAVL **T){
    TreeAVL *U, *V;
    U = (*T) -> left;
    V = U -> right;
    
    U -> right = V -> left;
    V -> left = U;
    (*T) -> left = V -> right;
    V -> right = (*T);
    
    (*T)->fb = (V->fb == -1) ? 1 : 0;
    U->fb = (V->fb == 1) ? -1 : 0;
    
    *T = V;
}

//esquerda
void caso2(TreeAVL **T, int *H){
    TreeAVL *U;
    U = (*T)->right;
    if(U->fb==1){
        rotationLeft(T); //1.1
    }else{
        rotationDuoLeft(T); //1.2
    }
    (*T)->fb = 0;
    *H = 0;
}

//direita
void caso1(TreeAVL **T, int *H){
    TreeAVL *U;
    U = (*T)->left;
    if(U->fb==-1){
        rotationRight(T); //1.1
    }else{
        rotationDuoRight(T); //1.2
    }
    (*T)->fb = 0;
    *H = 0;
}

int main() {
    printf("TreeAVL\n");
    TreeAVL *T = NULL;
    int num = 1;
    /*for (i=0; i<8; i++) {
        scanf("%d", &num);
        insertAVL(&T, num, &num);
    }*/
    insertAVL(&T,70,&num);
    insertAVL(&T,50,&num);
    insertAVL(&T,80,&num);
    insertAVL(&T,90,&num);
    insertAVL(&T,71,&num);
    //preOrdem(T);
    insertAVL(&T,75,&num);
    
    insertAVL(&T, 73, &num);
    insertAVL(&T, 74, &num);
    puts("simetrica:");
    ordemSimetrica(T);
    
    return 0;
}
