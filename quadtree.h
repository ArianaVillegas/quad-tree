//
// Created by suro on 2020-11-13.
//

#ifndef QUADTREE_QUADTREE_H
#define QUADTREE_QUADTREE_H

#include "CImg.h"
#include <fstream>

using namespace cimg_library;
using namespace std;

struct pixel_des{
    int xi, xf, yi, yf;
    int val;
};

bool isColorUnique(int xi, int yi, int xf, int yf, CImg<char> &image){
    int color = image(yi,xi);
    for(int i=xi; i<xf; i++){
        for(int j=yi; j<yf; j++){
            if(color != image(j,i))
                return false;
        }
    }
    return true;
}

void insert(int xi, int yi, int xf, int yf, CImg<char> &image, ofstream &output_file){
    bool unique = isColorUnique(xi,yi,xf,yf,image);
    if(unique){
        if(image(yi,xi) == -1) return;
        pixel_des pd = {xi, xf, yi, yf,image(yi,xi)};
        output_file.write((char*)&pd, sizeof(pixel_des));
    } else {
        int mx = (xf+xi)/2;
        int my = (yf+yi)/2;
        insert(xi,yi,mx,my,image,output_file);
        insert(mx,yi,xf,my,image,output_file);
        insert(xi,my,mx,yf,image,output_file);
        insert(mx,my,xf,yf,image,output_file);
    }
}


void insert(CImg<char> &image){
    int w = image.width();
    int h = image.height();
    ofstream output_file("output.txt", ios::binary | ios::trunc);
    insert(0,0,h,w,image,output_file);
}


CImg<char> reconstruir(int w, int h, string filename){
    ifstream input_file(filename, ios::binary);
    pixel_des pd;
    CImg<unsigned char> R(w,h, 1, 1, 255); 
    while(input_file.read((char*)&pd, sizeof(pixel_des))){
        for(int i=pd.xi;i<pd.xf;i++){
            for(int j=pd.yi;j<pd.yf;j++)
            {
                R(j,i) = 0;
            }
        }
    }
    return R;
}


#endif //QUADTREE_QUADTREE_H