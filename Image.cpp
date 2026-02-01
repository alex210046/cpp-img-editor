#include "Image.h"
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image.h"
#include "stb_image_write.h"

Image::Image() : width(0), height(0), channels(0) {};

Image::Image(int width, int height, int channels) : width(width), height(height), channels(channels) {};

int Image::getHeight() const {
    return height;
}

int Image::getWidth() const {
    return width;
}

bool Image::load(const string& file) {
    uint8_t * file_data = stbi_load(file.c_str(), &width, &height, &channels, 0);
    if (!file_data)
        return false;

    data.assign(file_data, file_data + (width * height * channels));
    stbi_image_free(file_data);

    return true;
}

bool Image::save(const string& file) {
    size_t dotPos = file.find_last_of(".");
    string ext;

    if (dotPos != string::npos)
        ext = file.substr(dotPos + 1);
    else
        return false;
    for (auto &c : ext)
        c = tolower(c);

    int success = 0;
    if (ext == "png")
        success = stbi_write_png(file.c_str(), width, height, channels, data.data(), width * channels);
    else if (ext == "jpg" || ext == "jpeg")
        success = stbi_write_jpg(file.c_str(), width, height, channels, data.data(), 90);
    else if (ext == "bmp")
        success = stbi_write_bmp(file.c_str(), width, height, channels, data.data());
    else
        return false;

    if (!success)
        return false;

    return true;
}

void Image::grayScale() {
    if (channels < 3)
        return;
    for (int it = 0; it < data.size(); it += channels) {
        uint8_t avg_col = (uint8_t)((data[it] + data[it + 1] + data[it + 2]) / 3);
        data[it] = avg_col;
        data[it + 1] = avg_col;
        data[it + 2] = avg_col;
    }
}

void Image::adjustBrightness(int value) {
    for (int it = 0; it < data.size(); it++) {
        int newVal = data[it] * value / 100;
        if (newVal > 255)
            newVal = 255;
        else if (newVal < 0)
            newVal = 0;
        data[it] = newVal;
    }
}

void Image::rotate90deg() {
    int newWidth = height;
    int newHeight = width;

    vector<uint8_t> newData(newWidth * newHeight * channels);
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int srcIndex = (y * width + x) * channels;
            int destX = height - 1 - y;
            int destY = x;
            int destIndex = (destY * newWidth + destX) * channels;
            for (int k = 0; k < channels; k++) {
                newData[destIndex + k] = data[srcIndex + k];
            }
        }
    }
    width = newWidth;
    height = newHeight;
    data = newData;
}