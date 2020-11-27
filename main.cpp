#include <iostream>
#include <vector>
#include "quadtree.h"

using namespace std;


CImg<char> Binarizar(CImg<float> & img, int umbral)
{
    CImg<char> R(img.width(),img.height());
    for(int i=0;i< img.width();i++)
        for(int j=0;j< img.height();j++)
        {
            int r = img(i,j,0);
            int g = img(i,j,1);
            int b = img(i,j,2);
            if ( (r+g+b)/3 > umbral)
                R(i,j) = 255;
            else
                R(i,j) = 0;
        }
    return R;
}


void tester(string filename, int &i, int threshold) {
    ifstream infile(filename);
    string path;

    clock_t tStart, tEnd;
    double timeTaken;
    int nNodos;
    cout << "Test\tInp Size  Ins Time  N nodes  Quad Size  Out Size  Comp Quad  Comp Img Rec Time  Treshold\n";
    while (getline(infile, path)) {
        nNodos = 0;
        cout << "test" << i << "\t";
        CImg<float> testImage(path.c_str());
        string nameImageInput = "input_images/input_image_"+ to_string(i) + ".jpg";
        string nameImageOutput = "output_images/output_image_"+ to_string(i) + ".jpg";
        string quadTreeFile = "quatrees_images/quadTree_image_"+ to_string(i) + ".bin";
        
        testImage.save(nameImageInput.c_str());
        long long inSIze = cimg::fsize(nameImageInput.c_str());
        cout << inSIze << "  ";

        tStart = clock();
        insert(testImage, threshold, quadTreeFile, nNodos);
        tEnd = clock();
        timeTaken = double(tEnd - tStart)/CLOCKS_PER_SEC; 
        long long quadSize = cimg::fsize(quadTreeFile.c_str());
        cout << timeTaken << "  "<< nNodos << "  " << quadSize << "  ";


        CImg<float> outputImage = reconstruir(testImage.width(),testImage.height(),quadTreeFile);
        tEnd = clock();
        timeTaken = double(tEnd - tStart)/CLOCKS_PER_SEC - timeTaken; 
        
        outputImage.save(nameImageOutput.c_str());
        long long outSize = cimg::fsize(nameImageOutput.c_str());
        cout << outSize << " " << 100 - (double) quadSize/ (double) inSIze*100 <<"% " << 100 - (double) outSize/ (double) inSIze*100 <<"% " << timeTaken << "  " << threshold << endl;

        i++;
    }

    infile.close();  
    
}

int main(){

    string filenameTestFile = "data.txt";
    int i=0;
    vector<int> thresholds = {10, 25, 50, 75};
    for (auto t:thresholds)
        tester(filenameTestFile, i, t);
    return 1;
}