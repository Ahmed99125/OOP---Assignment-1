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

int loadGreyImage(unsigned char img[][SIZE]);
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
void FilterGrey8();
void FilterGrey9();
void FilterGreyA();
void FilterGreyB();
void FilterGreyC();
void FilterGreyD();

void blur();

int main() {
    display();
}


int loadGreyImage(unsigned char img[][SIZE]) {
    cout << "Please enter file name of the image to process:" << endl;
    string fileName;
    cin >> fileName;
    fileName += ".bmp";
    char cwd[PATH_MAX];
    fileName = strcat(getcwd(cwd, sizeof(cwd)), "/") + fileName;
    return 1 - readGSBMP(fileName.c_str(), img);
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
    while (!loadGreyImage(image)) {
        cout << "Please enter a correct file name." << endl;
    }

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
            case '8':
                FilterGrey8();
                break;
            case '9':
                FilterGrey9();
                break;
            case 'a':
                FilterGreyA();
                break;
            case 'b':
                FilterGreyB();
            case 'c':
                FilterGreyC();
                break;
            case 'd':
                FilterGreyD();
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
    while (!loadGreyImage(image2)) {
        cout << "Please enter a correct file name." << endl;
    }

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
        cin >> c;
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
        cin >> x;
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

void FilterGrey8() { //Enlarge image
    int x = 0;
    cout << "Enter the quarter to enlarge from 1, 2, 3, 4: " << endl;
    cin >> x;
    while(x != 1 && x != 2 && x != 3 && x != 4) {
        cout << "Enter a valid input.\n";
        cin >> x;
    }
    unsigned char tmp[SIZE][SIZE];
    if(x == 1) {
        for(int i=0; i<SIZE / 2; ++i) {
            for(int j=0; j<SIZE / 2; ++j) {
                tmp[i * 2][j * 2] = image[i][j];
                tmp[i * 2 + 1][j * 2] = image[i][j];
                tmp[i * 2][j * 2 + 1] = image[i][j];
                tmp[i * 2 + 1][j * 2 + 1] = image[i][j];
            }
        }
    } else if(x == 2) {
        for(int i=0; i<SIZE / 2; ++i) {
            for(int j=SIZE / 2; j<SIZE; ++j) {
                tmp[i * 2][(j - SIZE / 2) * 2] = image[i][j];
                tmp[i * 2 + 1][(j - SIZE / 2) * 2] = image[i][j];
                tmp[i * 2][(j - SIZE / 2) * 2 + 1] = image[i][j];
                tmp[i * 2 + 1][(j - SIZE / 2) * 2 + 1] = image[i][j];
            }
        }
    } else if(x == 3) {
        for(int i=SIZE / 2; i<SIZE; ++i) {
            for(int j=0; j<SIZE / 2; ++j) {
                tmp[(i - SIZE / 2) * 2][j * 2] = image[i][j];
                tmp[(i - SIZE / 2) * 2 + 1][j * 2] = image[i][j];
                tmp[(i - SIZE / 2) * 2][j * 2 + 1] = image[i][j];
                tmp[(i - SIZE / 2) * 2 + 1][j * 2 + 1] = image[i][j];
            }
        }
    } else {
        for(int i=SIZE / 2; i<SIZE; ++i) {
            for(int j=SIZE / 2; j<SIZE; ++j) {
                tmp[(i - SIZE / 2) * 2][(j - SIZE / 2) * 2] = image[i][j];
                tmp[(i - SIZE / 2) * 2 + 1][(j - SIZE / 2) * 2] = image[i][j];
                tmp[(i - SIZE / 2) * 2][(j - SIZE / 2) * 2 + 1] = image[i][j];
                tmp[(i - SIZE / 2) * 2 + 1][(j - SIZE / 2) * 2 + 1] = image[i][j];
            }
        }
    }

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            image[i][j] = tmp[i][j];
        }
    }

    showGrayImage();
}

void FilterGrey9() { // Shrink image
    int x = 0;
    cout << "Enter the ratio of shrink from 2, 3, 4: " << endl;
    cin >> x;
    while(x != 2 && x != 3 && x != 4) {
        cout << "Enter a valid input.\n";
        cin >> x;
    }
    if(x == 2) {
        unsigned char tmp[SIZE / 2][SIZE / 2];
        for(int i=0; i<SIZE; i += 2) {
            for(int j=0; j<SIZE; j += 2) {
                tmp[i / 2][j / 2] = (image[i][j] + image[i + 1][j] + image[i + 1][j + 1] + image[i][j + 1]) / 4;
            }
        }
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                image[i][j] = 255;
            }
        }
        for (int i = 0; i < SIZE / 2; i++) {
            for (int j = 0; j < SIZE / 2; j++) {
                image[i][j] = tmp[i][j];
            }
        }
    } else if(x == 3) {
        unsigned char tmp[SIZE / 3][SIZE / 3];
        for(int i=1; i<SIZE; i += 3) {
            for(int j=1; j<SIZE; j += 3) {
                tmp[i / 3][j / 3] = (image[i][j] + image[i + 1][j] + image[i + 1][j + 1] + image[i][j + 1] + image[i - 1][j] + image[i - 1][j - 1] + image[i][j - 1] + image[i + 1][j - 1] + image[i - 1][j + 1]) / 9;
            }
        }
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                image[i][j] = 255;
            }
        }
        for (int i = 0; i < SIZE / 3; i++) {
            for (int j = 0; j < SIZE / 3; j++) {
                image[i][j] = tmp[i][j];
            }
        }
    } else {
        unsigned char tmp[SIZE / 4][SIZE / 4];
        for(int i=0; i<SIZE; i += 4) {
            for(int j=0; j<SIZE; j += 4) {
                tmp[i / 4][j / 4] = (image[i][j] + image[i + 1][j] + image[i + 1][j + 1] + image[i][j + 1] + image[i - 1][j] + image[i - 1][j - 1] + image[i][j - 1] + image[i + 1][j - 1] + image[i - 1][j + 1] + image[i + 2][j + 1] + image[i + 2][j + 2] + image[i][j + 2] + image[i + 2][j] + image[i + 1][j + 2] + image[i - 1][j + 2] + image[i + 2][j - 1]) / 16;
            }
        }
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                image[i][j] = 255;
            }
        }
        for (int i = 0; i < SIZE / 4; i++) {
            for (int j = 0; j < SIZE / 4; j++) {
                image[i][j] = tmp[i][j];
            }
        }
    }

    showGrayImage();
}

void FilterGreyA() { // Mirror 1/2 image
    int x = 0;
    cout << "Enter the part you want to mirror 1(top-down), 2(down-top), 3(left-right), 4(right-left): " << endl;
    cin >> x;
    while(x != 1 && x != 2 && x != 3 && x != 4) {
        cout << "Enter a valid input.\n";
        cin >> x;
    }
    if(x == 1) {
        for(int i=0; i<SIZE / 2; ++i) {
            for(int j=0; j<SIZE; ++j) {
                image[SIZE - i - 1][j] = image[i][j];
            }
        }
    } else if(x == 2) {
        for(int i=SIZE / 2; i<SIZE; ++i) {
            for(int j=0; j<SIZE; ++j) {
                image[SIZE - i - 1][j] = image[i][j];
            }
        }
    } else if(x == 3) {
        for(int i=0; i<SIZE; ++i) {
            for(int j=0; j<SIZE / 2; ++j) {
                image[i][SIZE - j - 1] = image[i][j];
            }
        }
    } else {
        for(int i=0; i<SIZE; ++i) {
            for(int j=SIZE / 2; j<SIZE; ++j) {
                image[i][SIZE - j - 1] = image[i][j];
            }
        }
    }

    showGrayImage();
}

void FilterGreyB() { // Shuffle Image
    int w, x, y, z;
    cout << "New order of quarters ?" << endl;
    cin >> w >> x >> y >> z;
    while(w < 1 || w > 4 || x < 1 || x > 4 || y < 1 || y > 4 || z < 1 || z > 4) {
        cout << "Enter a valid input.\n";
        cin >> w >> x >> y >> z;
    }
    unsigned char tmp1[SIZE / 2][SIZE / 2];
    unsigned char tmp2[SIZE / 2][SIZE / 2];
    unsigned char tmp3[SIZE / 2][SIZE / 2];
    unsigned char tmp4[SIZE / 2][SIZE / 2];
    for(int i=0; i<SIZE / 2; ++i) {
        for(int j=0; j<SIZE / 2; ++j) {
            tmp1[i][j] = image[i][j];
        }
    }
    for(int i=0; i<SIZE / 2; ++i) {
        for(int j=SIZE / 2; j<SIZE; ++j) {
            tmp2[i][j - SIZE / 2] = image[i][j];
        }
    }
    for(int i=SIZE / 2; i<SIZE; ++i) {
        for(int j=0; j<SIZE / 2; ++j) {
            tmp3[i - SIZE / 2][j] = image[i][j];
        }
    }
    for(int i=SIZE / 2; i<SIZE; ++i) {
        for(int j=SIZE / 2; j<SIZE; ++j) {
            tmp4[i - SIZE / 2][j - SIZE / 2] = image[i][j];
        }
    }

    if(w == 1) {
        for(int i=0; i<SIZE / 2; ++i) {
            for(int j=0; j<SIZE / 2; ++j) {
                image[i][j] = tmp1[i][j];
            }
        }
    } else if(w == 2) {
        for(int i=0; i<SIZE / 2; ++i) {
            for(int j=0; j<SIZE / 2; ++j) {
                image[i][j] = tmp2[i][j];
            }
        }
    } else if(w == 3) {
        for(int i=0; i<SIZE / 2; ++i) {
            for(int j=0; j<SIZE / 2; ++j) {
                image[i][j] = tmp3[i][j];
            }
        }
    } else if(w == 4) {
        for(int i=0; i<SIZE / 2; ++i) {
            for(int j=0; j<SIZE / 2; ++j) {
                image[i][j] = tmp4[i][j];
            }
        }
    }

    if(x == 1) {
        for(int i=0; i<SIZE / 2; ++i) {
            for(int j=SIZE / 2; j<SIZE; ++j) {
                image[i][j] = tmp1[i][j - SIZE / 2];
            }
        }
    } else if(x == 2) {
        for(int i=0; i<SIZE / 2; ++i) {
            for(int j=SIZE / 2; j<SIZE; ++j) {
                image[i][j] = tmp2[i][j - SIZE / 2];
            }
        }
    } else if(x == 3) {
        for(int i=0; i<SIZE / 2; ++i) {
            for(int j=SIZE / 2; j<SIZE; ++j) {
                image[i][j] = tmp3[i][j - SIZE / 2];
            }
        }
    } else if(x == 4) {
        for(int i=0; i<SIZE / 2; ++i) {
            for(int j=SIZE / 2; j<SIZE; ++j) {
                image[i][j] = tmp4[i][j - SIZE / 2];
            }
        }
    }

    if(y == 1) {
        for(int i=SIZE / 2; i<SIZE; ++i) {
            for(int j=0; j<SIZE / 2; ++j) {
                image[i][j] = tmp1[i - SIZE / 2][j];
            }
        }
    } else if(y == 2) {
        for(int i=SIZE / 2; i<SIZE; ++i) {
            for(int j=0; j<SIZE / 2; ++j) {
                image[i][j] = tmp2[i - SIZE / 2][j];
            }
        }
    } else if(y == 3) {
        for(int i=SIZE / 2; i<SIZE; ++i) {
            for(int j=0; j<SIZE / 2; ++j) {
                image[i][j] = tmp3[i - SIZE / 2][j];
            }
        }
    } else if(y == 4) {
        for(int i=SIZE / 2; i<SIZE; ++i) {
            for(int j=0; j<SIZE / 2; ++j) {
                image[i][j] = tmp4[i - SIZE / 2][j];
            }
        }
    }

    if(z == 1) {
        for(int i=SIZE / 2; i<SIZE; ++i) {
            for(int j=SIZE / 2; j<SIZE; ++j) {
                image[i][j] = tmp1[i - SIZE / 2][j - SIZE / 2];
            }
        }
    } else if(z == 2) {
        for(int i=SIZE / 2; i<SIZE; ++i) {
            for(int j=SIZE / 2; j<SIZE; ++j) {
                image[i][j] = tmp2[i - SIZE / 2][j - SIZE / 2];
            }
        }
    } else if(z == 3) {
        for(int i=SIZE / 2; i<SIZE; ++i) {
            for(int j=SIZE / 2; j<SIZE; ++j) {
                image[i][j] = tmp3[i - SIZE / 2][j - SIZE / 2];
            }
        }
    } else if(z == 4) {
        for(int i=SIZE / 2; i<SIZE; ++i) {
            for(int j=SIZE / 2; j<SIZE; ++j) {
                image[i][j] = tmp4[i - SIZE / 2][j - SIZE / 2];
            }
        }
    }

    showGrayImage();
}

void FilterGreyC() { // Blur Image
    for (int i = 0; i < 4; i++) {
        blur();
    }

    showGrayImage();
}

void FilterGreyD() { // Crop Filter
    int x, y, l, w;
    cout << "Please enter x y l w: " << endl;
    cin >> x >> y >> l >> w;
    while (x < 0 || x > 256 || y < 0 || y > 256 || l < 0 || l > 256 || w < 0 || w > 256) {
        cout << "Please enter valid input." << endl;
        cin >> x >> y >> l >> w;
    }

    unsigned char tmp[SIZE][SIZE];
    cout << SIZE << endl;

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            tmp[i][j] = 255;
        }
    }

    for (int i = x; i < x+l; i++) {
        for (int j = y; j < y+w; j++) {
            tmp[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            image[i][j] = tmp[i][j];
        }
    }

    showGrayImage();
}

void FilterGreyE() { // Skew Image
    int x;
    cout << "Please enter degree to skew right:" << endl;
    cin >> x;
    x = ((x%360)+360) % 360;

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