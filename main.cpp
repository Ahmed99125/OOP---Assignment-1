#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <cmath>
#include <unistd.h>
#include "bmplib.cpp"

using namespace std;

using namespace std;
unsigned char image[SIZE][SIZE];

void loadGreyImage();
void saveGreyImage();
void display();

int main() {
    display()
}


void loadGreyImage() {
    string fileName;
    cin >> fileName;
    fileName += ".bmp";
    char cwd[PATH_MAX];
    fileName = strcat(getcwd(cwd, sizeof(cwd)), "/imgs/") + fileName;
    readGSBMP(fileName.c_str(), image);
}

void saveGreyImage() {
    string fileName;
    cin >> fileName;
    fileName += ".bmp";
    char cwd[PATH_MAX];
    fileName = strcat(getcwd(cwd, sizeof(cwd)), "/imgs/") + fileName;
    writeGSBMP(fileName.c_str(), image);
}

void display() {
    int option = -1;
}



void Filter1(){ // Black and White Image
    for(int i=0; i<SIZE; ++i) {
        for(int j=0; j<SIZE; ++j) {
            if(image[i][j] <= 127)
                image[i][j] = 0;
            else if(image[i][j] > 127)
                image[i][j] = 255;
        }
    }
}
void Filter2(){ // : Invert Image
    for(int i=0; i<SIZE; ++i) {
        for(int j=0; j<SIZE; ++j) {
            image[i][j] = 255 - image[i][j];
        }
    }
}
void Filter3(){ // Merge Images
    int matrix2[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0 ,0}};
    for(int i=0; i<SIZE; ++i) {
        for(int j=0; j<SIZE; ++j) {
            image[i][j] = (image[i][j] + matrix2[i][j]) / 2;
        }
    }
}
void Filter4(){ //Flip Image
    for(int i=0; i<SIZE; ++i) {
        for(int j=0; j<SIZE; ++j) {
            int temp = image[x][y];
            image[x][y]=image[SIZE-i][j]
            matrix[SIZE-i][j]=temp;
        }
    }

}
void Filter5(){ // Rotate Image
    int matrix2[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0 ,0}};

// rotate 90 deg

    for(int i=0; i<SIZE; ++i) {
        for(int j=0; j<SIZE; ++j) {
            image[i][j] = matrix2[SIZE - 1 - j][i];
        }
    }

// rotate 180 deg

    for(int i=SIZE - 1; i>-1; --i) {
        for(int j=SIZE - 1; j>-1; --j) {
            image[i][j] = matrix2[SIZE - i][SIZE - j];
        }
    }

// rotate 270 deg
    //! run both 90 deg then 180 deg

}
void Filter6(){ // Darken and Lighten Image
    for(int i=0; i<SIZE; ++i) {
        for(int j=0; j<SIZE; ++j) {
            // plus for ligher
            image[i][j] = image[i][j] + floor(.5 * image[i][j]);
            // minus for darker
            image[i][j] = image[i][j] - floor(.5 * image[i][j]);
        }
    }
}