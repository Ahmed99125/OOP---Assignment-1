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
    display();
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
    cout << "Please enter file name of the image to process:" << endl;
    loadGreyImage();

    cout << "Please select a filter to apply or 0 to exit:" << endl;
    cout << "1- Black & White Filter" << endl;
    cout << "2- Invert Filter" << endl;
    cout << "3- Merge Filter" << endl;
    cout << "4- Flip Filter" << endl;
    cout << "5- Darken and Lighten Image" << endl;
    cout << "6- Rotate Image" << endl;
    cout << "7- Detect Image Edges" << endl;
    cout << "8- Enlarge Image" << endl;
    cout << "9- Shrink Image" << endl;
    cout << "a- Mirror 1/2 Image" << endl;
    cout << "b- Shuffle Image" << endl;
    cout << "c- Blur Image" << endl;
    cout << "d- Crop Image" << endl;
    cout << "e- Skew Image Right" << endl;
    cout << "f- Skew Image Up" << endl;
    cout << "s- Save the image to a file" << endl;
    cout << "0- Exit" << endl;

    int option = -1;
    do {
        cin >> option;
        switch (option) {
            case 1:
                Filter1();
                break;
            case 2:
                Filter2();
                break;
            case 3:
                Filter3();
                break;
            case 4:
                Filter4();
                break;
            case 5:
                Filter5();
                break;
            case 6:
                Filter6();
                break;
            default:
                break;
        }
    } while (option != 0);
}