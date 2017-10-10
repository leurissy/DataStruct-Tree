//
//  TreeBlackRed.c
//  TreeBlackRed
//
//  Created by Larissa Cristina on 04/10/17.
//  Copyright © 2017 Larissa Cristina. All rights reserved.
//

#include "TreeBlackRed.h"
#define KRED "\x1B[31m"
#define RESET "\x1B[0m"
//VERIFICA A COR
int cor(TreeBlackRed* H){
    if(H==NULL)
        return BLACK;
    else
        return H->cor;
}

//Troca a Cor
void trocaCor(TreeBlackRed** H){
    (*H)->cor = !(*H)->cor;
    if((*H)->esq !=NULL)
        (*H)->esq->cor = !(*H)->esq->cor;
    if((*H)->dir !=NULL)
        (*H)->dir->cor = !(*H)->dir->cor;
    
}

//Rotacao Simples Esquerda
TreeBlackRed* rotacionaEsquerda(TreeBlackRed** T){
    TreeBlackRed* U = (*T)->dir;
    (*T)->dir = U->esq;
    U->esq = (*T);
    U->cor = (*T)->cor;
    (*T)->cor = RED;
    return (*T);
}

//Rotacao Simples Direita
TreeBlackRed* rotacionaDireita(TreeBlackRed** T){
    TreeBlackRed* U = (*T)->dir;
    (*T)->esq = U->dir;
    U->dir = (*T);
    U->cor = (*T)->cor;
    (*T)->cor = RED;
    return (*T);
}

//Rotacao dupla Esquerda
TreeBlackRed* duoEsqRED(TreeBlackRed** H){
    trocaCor(H);
    if(cor((*H)->dir->esq) == RED){
        (*H)->dir = rotacionaDireita(&((*H))->dir);
        (*H) = rotacionaEsquerda(H);
        trocaCor(H);
    }
    return (*H);
}

//Rotacao dupla Direita
TreeBlackRed* duoDirRED(TreeBlackRed** H){
    trocaCor(H);
    if(cor((*H)->esq->esq) == RED){
        (*H)->esq = rotacionaEsquerda(&((*H))->esq);
        (*H) = rotacionaDireita(H);
        trocaCor(H);
    }
    return (*H);
}

//Balancear
TreeBlackRed* balancear(TreeBlackRed** H){
    if(cor((*H)->dir) == RED){
     (*H) = rotacionaEsquerda(H);
    }
    if((*H)->esq != NULL && cor((*H)->dir) == RED && cor((*H)->esq->esq) == RED){
       (*H) = rotacionaDireita(H);
    }
    if(cor((*H)->esq)== RED && cor((*H)->dir)==RED){
        trocaCor(H);
    }
    return (*H);
}

//insere NO
void insereNO(TreeBlackRed** H, int valor, int *flag){
    if((*H) == NULL){
        TreeBlackRed* novo = (TreeBlackRed*)malloc(sizeof(TreeBlackRed));
        novo->info = valor;
        novo->cor = RED;
        novo->esq = NULL;
        novo->dir = NULL;
        *flag = 1; // foi
        (*H) = novo;
       // return (*H);
    }else{
        if(valor == (*H)->info)
            *flag = 0;
        else{
            if((*H)->info > valor)
                 insereNO(&((*H)->esq),valor,flag);
            else
                 insereNO(&((*H)->dir),valor,flag);
        }

        if(cor((*H)->dir) == RED && cor((*H)->esq) == BLACK)
            (*H) = rotacionaDireita(H);
        if(cor((*H)->esq) == RED && cor((*H)->esq->esq) == RED)
            (*H) = rotacionaEsquerda(H);
        if(cor((*H)->esq) == RED && cor((*H)->dir) == RED)
            trocaCor(H);
        //return (*H);
    }
}

//Insere na Arvore
int insere_TreeBlackRed(TreeBlackRed** T, int valor){
    int resp = 0;
    insereNO(T,valor,&resp);
    if((*T) != NULL)
        (*T)->cor = BLACK;
    return resp;
}

//Funcao de preOrdem
void preOrdem(TreeBlackRed *T){
    if (T != NULL){
        if(T->cor == RED){
            printf(KRED "%d\n", T->info);
        }else{
            printf(RESET "%d\n", T->info);
        }
        preOrdem(T->esq);
        preOrdem(T->dir);
    }
}

//Inicializa a Arvore
TreeBlackRed* inicializa_TreeBlackRed(){
    TreeBlackRed *T;
    T = NULL;
    return T;
}

//Remove o menor NO
TreeBlackRed* removerMenor(TreeBlackRed** T){
    if((*T)->esq == NULL){
        free(T);
        return NULL;
    }
    if(cor((*T)->esq)==BLACK &&  cor((*T)->esq->esq)==BLACK){
        (*T) = duoEsqRED(T);
    }
    (*T)->esq = removerMenor(&((*T)->esq));
    return balancear(T);
}

//Procura o menor NO
TreeBlackRed* procurarMenor(TreeBlackRed* atual){
    TreeBlackRed *U = atual;
    TreeBlackRed *V = atual->esq;
    while(V!=NULL){
        U = V;
        V = V->esq;
    }
    return U;
}

//Consultar se o NO pertence a arvore
int consulta_TreeBlackRed(TreeBlackRed* T, int info){
    if(T != NULL){
        if(T->info == info){
            return 1;
        }
        else{
            if(T->info > info){
                return consulta_TreeBlackRed(T->esq, info);
            }
            else{
                return consulta_TreeBlackRed(T->dir, info);
            }
        }
    }
    return 0;
}

int remove_TreeBlackTree(TreeBlackRed **T, int valor){
    if(consulta_TreeBlackRed((*T), valor)){
        //TreeBlackRed* h = (*T);
        if((*T) != NULL){
            (*T)->cor = BLACK;
        }
        return 1;
    }else
        return 0;
}

//Remover NO
TreeBlackRed* removeNO(TreeBlackRed** H, int valor){
    if (valor < (*H)->info){
        if(cor((*H)->esq)==BLACK && cor((*H)->esq->esq)==BLACK)
            (*H) = duoEsqRED(H);
        (*H)->esq = removeNO(&((*H)->esq),valor);
    }else{
        if(cor((*H)->esq) == RED){
            (*H) = rotacionaDireita(H);
            if(valor == (*H)-> info && ((*H)->dir == NULL)){
                free(H);
                return NULL;
            }
        }
        if(cor((*H)->dir) == BLACK && cor((*H)->dir->esq)==BLACK){
            (*H) = duoDirRED(H);
        }
        if(valor == (*H)->info){
            TreeBlackRed* U = procurarMenor((*H)->dir);
            (*H)->info = U->info;
            (*H)->dir = removerMenor(&((*H)->dir));
        }else{
            (*H)->dir = removeNO(&((*H)->dir),valor);
        }
    }
    return balancear(H);
}

       int main(){
           TreeBlackRed * T = NULL;
           
           insere_TreeBlackRed(&(T), 11);
           insere_TreeBlackRed(&(T), 10);
           insere_TreeBlackRed(&(T), 12);
           //insere_TreeBlackRed(&(T), 3);
           //remove_TreeBlackTree(&(T), 0);
           //insere_TreeBlackRed(&(T), 4);
           //insere_TreeBlackRed(&(T), 5);
           preOrdem(T);
           return 0;
       }
