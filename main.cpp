#include <bmplib.cpp>
#include <string>

using namespace std;
char image[SIZE][SIZE];

void loadGreyImage();
void saveGreyImage();

int main() {

}

void loadGreyImage() {
    string s;
    cin >> s;
    s += ".bmp";
    readGSBMP(s, image);
}

void saveGreyImage() {
    stirng s;
    cin >> s;
    s += ".bmp";
    writeGSBMP(s, image);
}