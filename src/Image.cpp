#include "Image.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

Image::Image(std::string fileName) {
    std::ifstream imgFile(fileName, std::ios::binary);

    unsigned char **imageBytes = new unsigned char *[height];
    string line;
    while (!imgFile.eof()) {
        getline(imgFile, line);
        cout << line << endl;
    }

    imgFile.close();

    imageData = imgFile;
}


Image::~Image() {

}
