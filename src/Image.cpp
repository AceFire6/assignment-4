#include "Image.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>


namespace MLLJET001 {
    Image::Image() {
        width = 0;
        height = 0;
        filename = "";
    }

    void Image::save(std::string file) {
        std::ofstream imgOut(file, std::ios::out | std::ios::binary);
        if (!imgOut.is_open()) {
            std::cout << "Can't create file: " << file << std::endl;
            exit(0);
        }

        // The PGM file header.
        imgOut << "P5" << std::endl;
        imgOut << "# " << file << std::endl;
        imgOut << width << " " << height << std::endl;
        imgOut << "255" << std::endl;

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
            std::cout << "File " << file << " not found" << std::endl;
            exit(0);
        }

        std::string line;
        while (!imgFile.eof()) {
            getline(imgFile, line);
            if (line[0] == '#' || line == "P5") {
                continue;
            } else if (line == "255") { // The last line of the header.
                break;
            } else {
                std::stringstream ss(line);
                std::string num;
                getline(ss, num, ' ');
                width = std::stoi(num);
                getline(ss, num, ' ');
                height = std::stoi(num);
            }
        }
        unsigned char *imageBytes = new unsigned char [height*width];
        imgFile.read((char *) imageBytes, height * width);
        imgFile.close();

        imageData = std::unique_ptr<unsigned char []>(imageBytes);
    }
}
