#pragma once
#include <vector>
#include <string>

struct Pixel {
    unsigned char r, g, b;
};

struct Image {
    int width, height;
    std::vector<Pixel> data;
};

struct GrayImage {
    int width, height;
    std::vector<unsigned char> data;
};

struct BinaryImage {
    int width, height;
    std::vector<unsigned char> data;
};

struct MyPoint {
    int x, y;
};

// Function declarations
Image loadImage(const std::string& filename);
GrayImage toGray(const Image& img);
BinaryImage threshold(GrayImage& gray, int T);
BinaryImage edgeDetection(const BinaryImage& bin);
std::vector<MyPoint> findContour(const BinaryImage& edge);