#ifndef IMAGE_H
#define IMAGE_H
#include <cstdint>
#include <string>
#include <vector>
#include <iostream>
using namespace std;

class Image {
    private:
        int width, height, channels;
        vector<uint8_t> data;
    public:
        Image();
        Image(int width, int height, int channels);
        int getWidth() const;
        int getHeight() const;
        bool load(const string& file);
        bool save(const string& file);
        void grayScale();
        void adjustBrightness(int value);
        void rotate90deg();
};

#endif