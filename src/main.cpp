#include <iostream>

#include "Image.h"

using namespace std;


int main(int argc,  const char* argv[]) {
    if (argc < 2) {
        cout << "Too few arguments." << endl;
        return 0;
    }

    string command = argv[1];

    string image1Name = argv[2];
    MLLJET001::Image img1;
    img1 << image1Name;

    string outputName = argv[argc-1];
    MLLJET001::Image imgOut;

    if (command == "-a") { // Add
        MLLJET001::Image img2;
        img2 << argv[3];

        imgOut = img1 + img2;
    } else if (command == "-s") { // Subtract
        MLLJET001::Image img2;
        img2 << argv[3];

        imgOut = img1 - img2;
    } else if (command == "-i") { // Invert
        imgOut = !img1;
        imgOut >> outputName;
    } else if (command == "-l") { // Mask
        MLLJET001::Image img2;
        img2 << argv[3];

        imgOut = img1 / img2;
    } else if (command == "-t") { // Threshold
        int threshold = stoi(argv[3]);

        imgOut = img1 * threshold;
    } else {
        cout << "Command: " << command << " not recognized.";
        return 0;
    }
    imgOut >> outputName;
    return 0;
}
