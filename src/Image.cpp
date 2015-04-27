#include "Image.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

namespace MLLJET001 {
    Image::Image() {
        width = 0;
        height = 0;
        filename = "";
    }

    Image::~Image() {
        // TODO delete [] imageData.get();
    }

    void Image::save(std::string file) {
        std::ofstream imgOut(file, std::ios::out | std::ios::binary);
        if (!imgOut.is_open()) {
            cout << "Can't create file: " << file << endl;
            exit(0);
        }

        imgOut << "P5" << endl;
        imgOut << "# " << file << endl;
        imgOut << width << " " << height << endl;
        imgOut << "255" << endl;

        ImageIterator imgIter = this->begin();
        while (imgIter != this->end()) {
            imgOut << *imgIter;
            imgIter++;
        }
        imgOut.close();
    }

    void Image::load(std::string file) {
        this->filename = file;
        std::ifstream imgFile(file, std::ios::binary);
        if (!imgFile.is_open()) {
            cout << "File " << file << " not found" << endl;
            exit(0);
        }

        string line;
        while (!imgFile.eof()) {
            getline(imgFile, line);
            if (line[0] == '#' || line == "P5") {
                continue;
            } else if (line == "255") {
                break;
            } else {
                stringstream ss(line);
                string num;
                getline(ss, num, ' ');
                width = stoi(num);
                getline(ss, num, ' ');
                height = stoi(num);
            }
        }
        unsigned char *imageBytes = new unsigned char [height*width];
        imgFile.read((char *) imageBytes, height * width);
        imgFile.close();

        imageData = unique_ptr<unsigned char []>(imageBytes);
    }
}
