//
//  AVL2.h
//  TreeAVL
//
//  Created by Larissa Cristina on 03/10/17.
//  Copyright © 2017 Larissa Cristina. All rights reserved.
//

#ifndef AVL2_h
#define AVL2_h

#include <stdio.h>
#include <stdlib.h>

struct TAVL{
    int info;
    int fb;
    struct TAVL *left;
    struct TAVL *right;
};

typedef struct TAVL TreeAVL;

void caso1(TreeAVL **T, int H);

void caso2(TreeAVL **T, int H);
#endif /* AVL2_h */
