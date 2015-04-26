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
    MLLJET001::Image img1(image1Name);
    img1.load();

    string outputName = argv[argc-1];
    MLLJET001::Image imgOut(outputName);

    if (command == "-a") { // Add
        MLLJET001::Image img2(argv[3]);
        img2.load();

        imgOut = img1 + img2;
        imgOut.save();
    } else if (command == "-s") { // Subtract
        MLLJET001::Image img2(argv[3]);
        img2.load();

        imgOut = img1 - img2;
        imgOut.save();
    } else if (command == "-i") { // Invert
        imgOut = !img1;
        imgOut.save();
    } else if (command == "-l") { // Mask
        MLLJET001::Image img2(argv[3]);
        img2.load();

        imgOut = img1 / img2;
        imgOut.save();
    } else if (command == "-t") { // Threshold

    } else {
        cout << "Command not recognized.";
    }

    return 0;
}
