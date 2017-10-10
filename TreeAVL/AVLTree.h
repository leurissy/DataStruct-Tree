//
//  AVLTree.h
//  AED II
//
//  Created by Larissa Cristina on 20/09/17.
//  Copyright © 2017 Larissa Cristina. All rights reserved.
//

#ifndef AVLTree_h
#define AVLTree_h

#include <stdio.h>
#include <stdlib.h>

struct TAVL{
    int info;
    int fb;
    struct TAVL *left;
    struct TAVL *right;
};

typedef struct TAVL TreeAVL;

void caso1(TreeAVL **T, int *H);

void caso2(TreeAVL **T, int *H);

void rotationRight(TreeAVL **T);

void rotationDuoRight(TreeAVL **T);

void rotationLeft(TreeAVL **T);

void rotationDuoLeft(TreeAVL **T);

#endif /* AVLTree_h */
