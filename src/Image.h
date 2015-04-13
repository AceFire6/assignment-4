#ifndef ASSIGNMENT_4_IMAGE_H
#define ASSIGNMENT_4_IMAGE_H

#include <string>
#include <memory>

class Image {
private:
    std::string imageName;
public:
    Image();
    Image(std::string fileName) : imageName(fileName) {};
    ~Image();

    int width;
    int height;
    std::unique_ptr<unsigned char **> imageData;

    Image operator+(const Image & image) {
        Image result;
        for (int i = 0; i < ; ++i) {
            
        }
        return result;
    }

};


#endif //ASSIGNMENT_4_IMAGE_H
