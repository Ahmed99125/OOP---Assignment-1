#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <cmath>
#include <unistd.h>
#include "bmplib.cpp"

using namespace std;

using namespace std;
unsigned char image[SIZE][SIZE], image2[SIZE][SIZE];

void loadGreyImage(unsigned char img[][SIZE]);
void saveGreyImage();
void saveGreyImage();
void showMenu();
void display();

void FilterGrey1();
void FilterGrey2();
void FilterGrey3();
void FilterGrey4();
void FilterGrey5();
void FilterGrey6();
void FilterGrey7();
void FilterGreyC();

void blur();

int main() {
    display();
}


void loadGreyImage(unsigned char img[][SIZE]) {
    string fileName;
    cin >> fileName;
    fileName += ".bmp";
    char cwd[PATH_MAX];
    fileName = strcat(getcwd(cwd, sizeof(cwd)), "/") + fileName;
    readGSBMP(fileName.c_str(), img);
}

void saveGreyImage() {
    string fileName;
    cin >> fileName;
    fileName += ".bmp";
    char cwd[PATH_MAX];
    fileName = strcat(getcwd(cwd, sizeof(cwd)), "/") + fileName;
    writeGSBMP(fileName.c_str(), image);
}

void showGrayImage() {
    writeGSBMP(".\\tmp\\img.bmp", image);
    system(".\\tmp\\img.bmp");
}

void display() {
    cout << "Please enter file name of the image to process:" << endl;
    loadGreyImage(image);

    char option = -1;
    do {
        showMenu();
        cin >> option;
        switch (option) {
            case '1':
                FilterGrey1();
                break;
            case '2':
                FilterGrey2();
                break;
            case '3':
                FilterGrey3();
                break;
            case '4':
                FilterGrey4();
                break;
            case '5':
                FilterGrey5();
                break;
            case '6':
                FilterGrey6();
                break;
            case '7':
                FilterGrey7();
                break;
            case 'c':
                FilterGreyC();
                break;
            default:
                break;
        }
    } while (option != 0);
}

void FilterGrey1(){ // Black and White Image
    for(int i = 0; i < SIZE; ++i) {
        for(int j = 0; j < SIZE; ++j) {
            if(image[i][j] <= 127)
                image[i][j] = 0;
            else
                image[i][j] = 255;
        }
    }

    showGrayImage();
}

void FilterGrey2(){ // : Invert Image
    for(int i = 0; i < SIZE; ++i) {
        for(int j = 0; j < SIZE; ++j) {
            image[i][j] = 255 - image[i][j];
        }
    }

    showGrayImage();
}

void FilterGrey3(){ // Merge Images
    cout << "Please enter name of image file to merge with:" << endl;
    loadGreyImage(image2);

    for(int i = 0; i < SIZE; ++i) {
        for(int j = 0; j < SIZE; ++j) {
            image[i][j] = (image[i][j] + image2[i][j]) / 2;
        }
    }

    showGrayImage();
}

void FilterGrey4(){ //Flip Image
    cout << "Flip (h)orizontally or (v)ertically ?" << endl;
    char c; cin >> c;
    while (c != 'h' && c != 'v') {
        cout << "please enter valid input." << endl;
    }
    if (c == 'h') {
        for(int i=0; i<SIZE; ++i) {
            for(int j=0; j<SIZE/2; ++j) {
                swap(image[i][j], image[i][SIZE-j]);
            }
        }
    }
    else if (c == 'v') {
        for(int i=0; i<SIZE/2; ++i) {
            for(int j=0; j<SIZE; ++j) {
                swap(image[i][j], image[SIZE-i][j]);
            }
        }
    }

    showGrayImage();
}

void FilterGrey5(){ // Darken and Lighten Image
    cout << "Do you want to (d)arken or (l)ighten?" << endl;
    char c; cin >> c;
    while (c != 'd' && c != 'l') {
        cout << "please enter valid input." << endl;
        cin >> c;
    }

    for(int i=0; i<SIZE; ++i) {
        for(int j=0; j<SIZE; ++j) {
            // plus for ligher
            if (c == 'l')
                image[i][j] += (SIZE-image[i][j])/2;
            // minus for darker
            else if (c == 'd')
                image[i][j] -= image[i][j]/2;
        }
    }

    showGrayImage();
}

void FilterGrey6(){ // Rotate Image
    cout << "Rotate (90), (180) or (270) degrees?" << endl;
    int x; cin >> x;
    while (x != 90 && x != 180 && x != 270) {
        cout << "please enter valid input." << endl;
    }


    auto rotate = []() {
        unsigned char tmp[SIZE][SIZE];

        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                tmp[j][SIZE-i] = image[i][j];
            }
        }

        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                image[i][j] = tmp[i][j];
            }
        }
    };

    switch (x) {
        case 90:
            // rotate 90 deg
            rotate();
            break;
        case 180:
            // rotate 180 deg
            for (int i = 0; i < 2; i++) {
                rotate();
            }
            break;
        case 270:
            // rotate 270 deg
            for (int i = 0; i < 3; i++) {
                rotate();
            }
            break;
        default:
            break;
    }

    showGrayImage();
}

void FilterGrey7() { // Edge Detector
    unsigned char tmp[SIZE][SIZE];

    // Sobel Edge Detector
    int multiply[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            int gx = 0, gy = 0;
            for (int x = -1; x < 2; x++) {
                for (int y = -1; y < 2; y++) {
                    if (i+x < 0 || i+x >= SIZE || j+y < 0 || j+y >= SIZE)
                        continue;
                    gx += image[i+x][j+y] * multiply[x+1][y+1];
                    gy += image[i+x][j+y] * multiply[y+1][x+1];
                }
            }
            gx *= gx, gy *= gy;
            if ((int)(round(sqrt(gx+gy))) > 180)
                tmp[i][j] = 0;
            else
                tmp[i][j] = 255;
        }
    }

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            image[i][j] = tmp[i][j];
        }
    }

    showGrayImage();
}

void FilterGreyC() { // Blur Image
    blur();

    showGrayImage();
}

void blur() {
    unsigned char tmp[SIZE][SIZE];

    int dx[] = {-1, -1, -1, 0, 0, 0, 1, 1, 1};
    int dy[] = {-1, 0, 1, -1, 0, 1, -1, 0, 1};

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            int avg = 0;
            for (int k = 0; k < 9; k++) {
                int x = i+dx[k], y = j+dy[k];
                if (x < 0 || x >= SIZE || y < 0 || y >= SIZE)
                    continue;
                avg += image[x][y];
            }
            tmp[i][j] = avg / 9;
        }
    }

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            image[i][j] = tmp[i][j];
        }
    }
}

void showMenu() {
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
}