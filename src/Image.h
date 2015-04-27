#ifndef IMAGE_H
#define IMAGE_H

#include <string>
#include <iostream>
#include <memory>

namespace MLLJET001 {
    class Image {
    public:
        Image();

        // Load the file in and parse it.
        void load(std::string file);
        // Save the file to the given path.
        void save(std::string file);

        // The name of the image file the object holds data of.
        std::string filename;
        int width;
        int height;
        // A unique ptr to the actual image data from the pgm file.
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

        // Copy Assignment Operator
        Image &operator=(const Image &rhs) {
            this->width = rhs.width;
            this->height = rhs.height;
            this->load(rhs.filename);
            return *this;
        }

        // Move Assignment Operator
        Image &operator=(Image &&rhs) {
            this->width = rhs.width;
            this->height = rhs.height;
            this->imageData = std::move(rhs.imageData);
            return *this;
        }

        // Used to add two images together. Clamps pixel values at 255.
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

        // Used to add two images together. Calls operator+=.
        Image operator+(const Image &image) {
            Image result(*this);
            if (result.width != image.width || result.height != image.height) {
                std::cout << "Images not of the same size." << std::endl;
                exit(0);
            }
            result += image;
            return result;
        }

        // Used to subtract two images from each other. Clamps pixel values at 0.
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

        // Used to subtract two images from each other. Calls operator-=.
        Image operator-(const Image &image) {
            Image result(*this);
            if (result.width != image.width || result.height != image.height) {
                std::cout << "Images not of the same size." << std::endl;
                exit(0);
            }
            result -= image;
            return result;
        }

        // Masking operator. If the mask's pixel value is 0, the pixel value is set to 0 too.
        Image operator/(const Image &image) {
            Image result(*this);
            if (result.width != image.width || result.height != image.height) {
                std::cout << "Images not of the same size." << std::endl;
                exit(0);
            }

            ImageIterator imgIter = result.begin();
            ImageIterator otherIter = image.begin();

            while (imgIter != result.end()) {
                if (*otherIter == 0) {
                    *imgIter = 0;
                }
                imgIter++;
                otherIter++;
            }
            return result;
        }

        // Inversion operator. Inverts the image this is applied to. p = (255 - p)
        Image operator!() {
            Image result(*this);
            ImageIterator imgIter = result.begin();
            while (imgIter != result.end()) {
                *imgIter = (unsigned char) (255 - *imgIter);
                imgIter++;
            }
            return result;
        }

        // Threshold operator. Turns all pixels that surpass the given threshold white, everything else black.
        Image operator*(const int threshold) {
            Image result(*this);
            ImageIterator imgIter = result.begin();
            while (imgIter != result.end()) {
                *imgIter = (unsigned char) ((*imgIter > threshold) ? 255 : 0);
                imgIter++;
            }
            return result;
        }

        // Operator that shortcuts to save the image with the filename given by the string.
        void operator>>(const std::string file) {
            this->save(file);
        }

        // Operator that shortcuts to load the image with the filename given by the string.
        void operator<<(const std::string file) {
            this->load(file);
        }

        // Iterator used for the image operations.
        class ImageIterator {
        private:
            // A pointer to the image data.
            unsigned char *pointer;
            int index;
        public:
            // Parametrized constructor that starts off at the beginning of the array.
            ImageIterator(unsigned char *ptr) : pointer(ptr), index(0) { }
            // Parametrized constructor that starts off at a given point in the array.
            ImageIterator(unsigned char *ptr, int count) : pointer(ptr), index(count) { }
            // Parametrized constructor that creates a copy of the supplied iterator.
            ImageIterator(const ImageIterator &copyIter) : pointer(copyIter.pointer), index(copyIter.index){ }

            // Increment the index of the interator.
            ImageIterator &operator++() {
                ++index;
                return *this;
            }

            // Increment the index of the interator.
            ImageIterator operator++(int) {
                ImageIterator tempIter(*this);
                operator++();
                return tempIter;
            }

            // Decrement the index of the interator.
            ImageIterator &operator--() {
                --index;
                return *this;
            }

            // Decrement the index of the interator.
            ImageIterator operator--(int) {
                ImageIterator tempIter(*this);
                operator--();
                return tempIter;
            }

            // Dereference the value of the array at the given index.
            unsigned char &operator*() {
                return pointer[index];
            }

            // Check to see if the iterators have the same index.
            bool operator!=(const ImageIterator &rhs) {
                return index != rhs.index;
            }

            // Move assignment operator.
            ImageIterator &operator=(const ImageIterator &rhs) {
                this->pointer = std::move(rhs.pointer);
                this->index = rhs.index;
                return *this;
            }
        };

        // Get the iterator for the current image.
        ImageIterator begin() const {
            return ImageIterator(this->imageData.get());
        }

        // Get the end of the iterator of the current image.
        ImageIterator end() {
            return ImageIterator(this->imageData.get(), width * height);
        }
    };
}

#endif //IMAGE_H
