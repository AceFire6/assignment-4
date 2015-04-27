#ifndef IMAGE_H
#define IMAGE_H

#include <string>
#include <iostream>
#include <memory>

namespace MLLJET001 {
    class Image {
    public:
        Image();

        ~Image();

        void load(std::string file);
        void save(std::string file);

        std::string filename;
        int width;
        int height;
        std::unique_ptr<unsigned char[]> imageData;

        // Copy Constructor
        Image(const Image &rhs) {
            this->filename = rhs.filename;
            this->width = rhs.width;
            this->height = rhs.height;
            this->load(this->filename);
        }

        // Move Constructor
        Image(Image &&rhs) {
            this->filename = std::move(rhs.filename);
            this->width = rhs.width;
            this->height = rhs.height;
            this->imageData = std::move(rhs.imageData);
        }

// Copy and Move Assignment Operators
        Image &operator=(const Image &rhs) {
            this->width = rhs.width;
            this->height = rhs.height;
            this->load(rhs.filename);
            return *this;
        }

        Image &operator=(Image &&rhs) {
            this->width = rhs.width;
            this->height = rhs.height;
            this->imageData = std::move(rhs.imageData);
            return *this;
        }

        Image operator+=(const Image &image) {
            ImageIterator imgIter = this->begin();
            ImageIterator otherIter = image.begin();
            while (imgIter != this->end()) {
                if ((*imgIter + *otherIter) > 255) {
                    *imgIter = 255;
                } else {
                    *imgIter = *imgIter + *otherIter;
                }
                imgIter++;
                otherIter++;
            }
            return *this;
        }

        Image operator+(const Image &image) {
            Image result(*this);
            if (result.width != image.width || result.height != image.height) {
                std::cout << "Images not of the same size." << std::endl;
                exit(0);
            }
            result += image;
            return result;
        }

        Image operator-=(const Image &image) {
            ImageIterator imgIter = this->begin();
            ImageIterator otherIter = image.begin();
            while (imgIter != end()) {
                if ((*imgIter - *otherIter) < 0) {
                    *imgIter = 0;
                } else {
                    *imgIter = *imgIter - *otherIter;
                }
                imgIter++;
                otherIter++;
            }
            return *this;
        }

        Image operator-(const Image &image) {
            Image result(*this);
            if (result.width != image.width || result.height != image.height) {
                std::cout << "Images not of the same size." << std::endl;
                exit(0);
            }
            result -= image;
            return result;
        }

        Image operator/(const Image &image) {
            Image result(*this);
            ImageIterator imgIter(result.imageData.get());
            ImageIterator otherIter = image.begin();
            if (result.width != image.width || result.height != image.height) {
                std::cout << "Images not of the same size." << std::endl;
                exit(0);
            }
            while (imgIter != end()) {
                if (*otherIter == 0) {

                }
                imgIter++;
                otherIter++;
            }
            return result;
        }

        Image operator!() {
            Image result(*this);
            ImageIterator imgIter(result.imageData.get());
            while (imgIter != end()) {
                *imgIter = (unsigned char) (255 - *imgIter);
                imgIter++;
            }
            return *this;
        }

        class ImageIterator {
        private:
            unsigned char *pointer;
            int counter;
        public:
            ImageIterator(unsigned char *ptr) : pointer(ptr), counter(0) { }

            ImageIterator(unsigned char *ptr, int count) : pointer(ptr), counter(count) { }

            ImageIterator(const ImageIterator &copyIter) : pointer(copyIter.pointer) { }

            ImageIterator &operator++() {
                ++counter;
                return *this;
            }

            ImageIterator operator++(int) {
                ImageIterator tempIter(*this);
                operator++();
                return tempIter;
            }

            ImageIterator &operator--() {
                --counter;
                return *this;
            }

            ImageIterator operator--(int) {
                ImageIterator tempIter(*this);
                operator--();
                return tempIter;
            }

            unsigned char &operator*() {
                return pointer[counter];
            }

            bool operator!=(const ImageIterator &rhs) {
                return counter != rhs.counter;
            }

            ImageIterator &operator=(const ImageIterator &rhs) {
                this->pointer = std::move(rhs.pointer);
                this->counter = rhs.counter;
                return *this;
            }
        };

        ImageIterator begin() const {
            return ImageIterator(this->imageData.get());
        }

        ImageIterator end() {
            return ImageIterator(this->imageData.get(), width * height);
        }
    };
}

#endif //IMAGE_H
