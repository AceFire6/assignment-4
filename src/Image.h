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
    std::unique_ptr<unsigned char []> imageData;

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

    }

    iterator begin() {
        return iterator(imageData.get());
    }

    iterator end() {
        return iterator(imageData.get(), width * height);
    }

    class iterator {
    private:
        unsigned char * pointer;
        int counter;
    public:
        iterator(unsigned char * ptr): pointer(ptr), counter(0) {}
        iterator(unsigned char * ptr, int count): pointer(ptr), counter(count) {}
        iterator(const iterator& copyIter) : pointer(copyIter.pointer) {}
        iterator& operator++() {
            ++counter;
            if (counter > 255) {
                counter = 255;
            }
            return *this;
        }
        iterator operator++(int) {
            iterator tempIter(*this);
            operator++();
            return tempIter;
        }

        iterator& operator--() {
            --counter;
            if (counter < 0) {
                counter = 0;
            }
            return *this;
        }
        iterator operator--(int) {
            iterator tempIter(*this);
            operator--();
            return tempIter;
        }

        unsigned char& operator*() {
            return pointer[counter];
        }

        iterator & operator=(const iterator & rhs) {
            iterator newIter(std::move(rhs.pointer), rhs.counter);
            return newIter;
        }
    };
};


#endif //ASSIGNMENT_4_IMAGE_H
