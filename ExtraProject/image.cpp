#include "image.h"
#include <opencv2/opencv.hpp> // Used only for imread
#include <iostream>
#include <vector>
#include <cmath>

// 1. Load image (using OpenCV)
Image loadImage(const std::string& filename) {
    cv::Mat mat = cv::imread(filename, cv::IMREAD_COLOR);
    if (mat.empty()) {
        std::cerr << "Error: Cannot open " << filename << std::endl;
        exit(1);
    }

    Image img;
    img.width = mat.cols;
    img.height = mat.rows;
    img.data.resize(img.width * img.height);

    for (int y = 0; y < img.height; y++) {
        for (int x = 0; x < img.width; x++) {
            cv::Vec3b color = mat.at<cv::Vec3b>(y, x);
            Pixel p = { color[2], color[1], color[0] }; // BGR -> RGB
            img.data[y * img.width + x] = p;
        }
    }
    return img;
}

// 2. Convert to grayscale
GrayImage toGray(const Image& img) {
    GrayImage gray;
    gray.width = img.width;
    gray.height = img.height;
    gray.data.resize(img.width * img.height);

    for (int i = 0; i < img.width * img.height; i++) {
        gray.data[i] = (unsigned char)(0.299 * img.data[i].r + 0.587 * img.data[i].g + 0.114 * img.data[i].b);
    }
    return gray;
}

// 3. Binarize (Object: white, Background: black)
BinaryImage threshold(GrayImage& gray, int T) {
    BinaryImage bin;
    bin.width = gray.width;
    bin.height = gray.height;
    bin.data.resize(gray.width * gray.height);

    for (int i = 0; i < gray.width * gray.height; i++) {
        bin.data[i] = (gray.data[i] > T) ? 0 : 255;
    }
    return bin;
}

// 4. Edge Detection
BinaryImage edgeDetection(const BinaryImage& bin) {
    BinaryImage edge;
    edge.width = bin.width;
    edge.height = bin.height;
    edge.data.assign(bin.width * bin.height, 0);
    // The binarized image can be used as the edge image directly.
    // This might be problematic if the contour is thicker than 1 pixel,
    // but for this example, simply copying the source is sufficient.
    // For a more precise implementation, an algorithm like Sobel should be used.
    return bin;
}


// 5. Extract contour (Final bug-fixed version)
std::vector<MyPoint> findContour(const BinaryImage& edge) {
    std::vector<MyPoint> contour;

    MyPoint startPoint = { -1, -1 };
    for (int y = 1; y < edge.height - 1; y++) {
        for (int x = 1; x < edge.width - 1; x++) {
            if (edge.data[y * edge.width + x] == 255) {
                startPoint = { x, y };
                goto found_start;
            }
        }
    }
found_start:
    if (startPoint.x == -1) return contour;

    contour.push_back(startPoint);

    MyPoint currentPoint = startPoint;

    // Clockwise search order: E, SE, S, SW, W, NW, N, NE
    int dx[] = { 1, 1, 0, -1, -1, -1, 0, 1 };
    int dy[] = { 0, 1, 1, 1, 0, -1, -1, -1 };

    int searchDir = 6; // Start searching from the West direction

    do {
        bool foundNext = false;
        for (int i = 0; i < 8; i++) {
            int nextDir = (searchDir + i) % 8;
            int nx = currentPoint.x + dx[nextDir];
            int ny = currentPoint.y + dy[nextDir];

            if (edge.data[ny * edge.width + nx] == 255) {
                currentPoint = { nx, ny };
                searchDir = (nextDir + 5) % 8;
                foundNext = true;
                break;
            }
        }

        if (!foundNext) break; // Exit if the next point is not found (safety break)

        if (currentPoint.x == startPoint.x && currentPoint.y == startPoint.y) {
            break; // Successfully terminate upon returning to the start point
        }

        contour.push_back(currentPoint);

    } while (true);

    return contour;
}