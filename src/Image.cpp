#include "Image.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

namespace MLLJET001 {
    Image::~Image() {
        // TODO delete [] imageData.get();
    }

    void Image::save() {
        // TODO Write file out
    }

    void Image::load() {
        std::ifstream imgFile(filename, std::ios::binary);
        if (!imgFile.is_open()) {
            cout << "File " << filename << " not found" << endl;
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
                cout << width << " " << height << endl;
            }
        }
        unsigned char *imageBytes = new unsigned char [height*width];
        imgFile.read((char *) imageBytes, height * width);
        imgFile.close();

        imageData = unique_ptr<unsigned char []>(imageBytes);
    }
}
