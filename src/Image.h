#ifndef ASSIGNMENT_4_IMAGE_H
#define ASSIGNMENT_4_IMAGE_H

#include <string>
#include <memory>

class Image {
public:
    Image();
    Image(std::string fileName);
    ~Image();

    int width;
    int height;
    std::unique_ptr<unsigned char **> imageData;

    // Copy Constructor
    Image(const Image &rhs) {

    }
    // Move Constructor
    Image(Image && rhs) {

    }
// Copy and Move Assignment Operators
    Image & operator=(const Image & rhs) {

    }

    Image & operator=(Image && rhs) {

    }

    Image operator+(const Image & image) {
        Image result;
        result.width = this->width;
        result.height = this->height;
        unsigned char ** newImageData = new unsigned char *[height];

        for (int row = 0; row < height; ++row) {
            newImageData[row] = new unsigned char[width];
            for (int col = 0; col < width; ++col) {
                newImageData[row][col] = *image.imageData.get()[row][col] + *this->imageData.get()[row][col];
            }
        }
//        std::unique_ptr<unsigned char **> newPtr(newImageData);
//        imageData = std::move(newPtr);

        return result;
    }
};


#endif //ASSIGNMENT_4_IMAGE_H
