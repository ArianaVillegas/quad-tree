//
// Created by suro on 2020-11-13.
//

#ifndef QUADTREE_QUADTREE_H
#define QUADTREE_QUADTREE_H

//#include "CImg.h"

//using namespace cimg_library;
using namespace std;
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

    vector<vector<bool>> image;
    node* root;
    int xi,yi;
    int w,h;

    bool isColorUnique(int xi, int yi, int xf, int yf){
        int color = image[yi][xi];
        for(int i=xi; i<xf; i++){
            for(int j=yi; j<yf; j++){
                cout << i << ' ' << j << ' ' << image[j][i] << ' ' << color << '\n';
                if(color != image[j][i])
                    return false;
            }
        }
        return true;
    }

    node* insert(int xi, int yi, int xf, int yf){
        bool unique = isColorUnique(xi,yi,xf,yf);
        cout << unique << endl;
        cout << "Inicio: " << xi << " " << yi << endl;
        cout << "Fin: " << xf << " " << yf << endl;
        if(unique){
            return new node(xi,yi,xf,yf,image[(xf+xi)/2][(yf+yi)/2],true);

            // guardar el nodo en disco
        } else {
            node* cur = new node(xi,yi,xf,yi,-1, false);
            int mx = (xf+xi)/2;
            int my = (yf+yi)/2;
            cur->children[0] = insert(xi,yi,mx,my);
            cur->children[1] = insert(mx,yi,xf,my);
            cur->children[2] = insert(xi,my,mx,yf);
            cur->children[3] = insert(mx,my,xf,yf);
            return cur;
        }
    }


public:

    quedtree(vector<vector<bool>> image){
        root = 0;
        this->image = image;
        this->xi = 0;
        this->yi = 0;
        this->w = image[0].size();
        this->h = image.size();
    }

    void insert(){
        root = insert(0,0,w,h);
    }


};

#endif //QUADTREE_QUADTREE_H