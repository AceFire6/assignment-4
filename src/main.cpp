#include <iostream>

using namespace std;


int main(int argc,  const char* argv[]) {
    if (argc < 2) {
        cout << "Too few arguments." << endl;
        return 0;
    }

    string command = argv[1];
    string image1Name = argv[2];
    string outputName = argv[argc-1];

    if (command == "-a") { // Add

    } else if (command == "-s") { // Subtract

    } else if (command == "-i") { // Invert

    } else if (command == "-l") { // Mask

    } else if (command == "-t") { // Threshold

    } else {
        cout << "Command not recognized.";
    }

    return 0;
}
