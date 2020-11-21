//
// Created by suro on 2020-11-13.
//

#ifndef QUADTREE_QUADTREE_H
#define QUADTREE_QUADTREE_H

#include "CImg.h"

using namespace cimg_library;

class quedtree{
    struct node{
        int xi, xf, yi, yf;
        int val;
        bool isTerminal;
        node* children[4];

        node(int xi, int xf, int yi, int yf, int val, bool isTerminal){
            this->xi = xi;
            this->yi = yi;
            this->xf = xf;
            this->yf = yf;
            this->val = val;
            this->isTerminal = isTerminal;
            for (int i=0; i<4; i++){
                children[i] = 0;
            }
        }
    };

    CImg<char> image;
    node* root;
    int xi,yi;
    int w,h;

    bool isColorUnique(int xi, int yi, int xf, int yf){
        int color = image(xi,yi);
        for(int i=xi; i<=xf; i++){
            for(int j=yi; j<=yf; j++){
                if(color != image(i,j))
                    return false;
            }
        }
        return true;
    }

    node* insert(int xi, int yi, int xf, int yf){
        if(isColorUnique(xi,yi,xf,yf)){
            return new node(xi,yi,xf,yf,image((xf-xi)/2,(yf-yi)/2),true);

            // guardar el nodo en disco
        } else {
            node* cur = new node(xi,yi,xf,yi,image((xf-xi)/2,(yf-yi)/2), false);
            cur->children[0] = insert(xi,yi,xf/2,yf/2);
            cur->children[1] = insert(xf/2,yi,xf,yf/2);
            cur->children[2] = insert(xi,yf/2,xf/2,yf);
            cur->children[3] = insert(xf/2,yf/2,xf,yf);
            return cur;
        }
    }


public:

    quedtree(CImg<char> image){
        root = 0;
        this->image = image;
        this->xi = 0;
        this->yi = 0;
        this->w = image.width();
        this->h = image.height();
    }

    void insert(){
        root = insert(0,0,w,h);
    }


};

#endif //QUADTREE_QUADTREE_H
