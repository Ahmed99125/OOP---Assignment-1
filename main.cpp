#include <bmplib.cpp>

using namespace std;
unsigned char image[SIZE][SIZE];

void loadGreyImage();
void saveGreyImage();

int main() {
    loadGreyImage();
    saveGreyImage();
}

void loadGreyImage() {
    char fileName[100];
    cin >> fileName;
    strcat(fileName, ".bmp");
    readGSBMP(fileName, image);
}

void saveGreyImage() {
    char fileName[100];
    cin >> fileName;
    strcat(fileName, ".bmp");
    writeGSBMP(fileName, image);
}