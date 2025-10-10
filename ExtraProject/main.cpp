#include <iostream>
#include <string>
#include <vector>
#include "image.h"
#include "feature.h"

using namespace std;

int main() {
    for (int i = 1; i <= 4; i++) { // additional 3 & 4 for prove the algorithm
        string filename = to_string(i) + ".jpg";
        //string filename = "C:\\Users\\jimmy\\Documents\\ImageProcessing\\project1\\ExtraProject\\ExtraProject\\ExtraProject\\1.jpg";
        //string filename = "C:\\Users\\jimmy\\Documents\\ImageProcessing\\3.jpg";

        // 1. Load image
        Image img = loadImage(filename);

        // 2. Convert to grayscale
        GrayImage gray = toGray(img);

        // 3. Binarize the image
        BinaryImage bin = threshold(gray, 128);

        // 4. Detect edges
        BinaryImage edge = edgeDetection(bin);

        // 5. Extract contour
        vector<MyPoint> contour = findContour(edge);

        // 6. Extract features
        ShapeFeature feat = extractFeatures(contour);

        // 7. Classify shape
        string shape = classifyShape(feat);

        // 8. Print the result
        cout << filename << " ¡æ " << shape << endl;
    }

    return 0;
}