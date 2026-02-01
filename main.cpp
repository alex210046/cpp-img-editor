#include "Image.h"
#include <iostream>
using namespace std;

bool handle(const string &instr, const int &value, Image &img) {
    if (instr == "grayscale") {
        img.grayScale();
        return true;
    }
    if (instr == "brightness") {
        img.adjustBrightness(value);
        return true;
    }
    if (instr == "rotate") {
        img.rotate90deg();
        return true;
    }

    return false;
}

int main(int argc, char* argv[]) {
    if (argc < 4) {
        cout << "Bad syntax!";
        return 0;
    }

    Image img;

    if (!img.load(argv[1])) {
        cerr << "Image load error!" << '\n';
        return 0;
    }
    cout << "Image " << argv[1] << " loaded " << img.getWidth() << " X " << img.getHeight() << '\n';

    int value = 0;
    string option = argv[3];
    if (argc == 5)
        value = stoi(argv[4]);
    if (!handle(option, value, img)) {
        cerr << "Unkown syntax\n";
        return 0;
    }

    if (!img.save(argv[2])) {
        cerr << "Image save error!" << '\n';
        return 0;
    }
    cout << "Saved file: " << argv[2] << '\n';

    return 0;
}