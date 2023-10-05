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