#include <iostream>
#include <string>
#include <vector>
#include <filesystem> // Add the filesystem library
#include <algorithm> // Required for the find function

#include "image.h"
#include "feature.h"

// Alias for the C++17 filesystem namespace
namespace fs = std::filesystem;
using namespace std;

// Function to convert a string to lowercase
string toLower(string s) {
    transform(s.begin(), s.end(), s.begin(),
        [](unsigned char c) { return tolower(c); });
    return s;
}

int main() {
    // List of allowed image file extensions to process
    const vector<string> allowed_extensions = { ".jpg", ".jpeg", ".png", ".bmp" };

    // Get the current path where the executable is located
    const fs::path current_path = ".";

    cout << "Searching for image files in the current folder..." << endl;

    // Iterate over all entries in the current path
    for (const auto& entry : fs::directory_iterator(current_path)) {
        // Check if it's a regular file
        if (entry.is_regular_file()) {
            fs::path file_path = entry.path();
            string extension = toLower(file_path.extension().string());

            // Check if the file's extension is in the allowed list
            auto it = find(allowed_extensions.begin(), allowed_extensions.end(), extension);

            if (it != allowed_extensions.end()) {
                string filename = file_path.filename().string();

                cout << "------------------------------------" << endl;
                cout << "Processing file: " << filename << endl;

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
                cout << filename << " -> " << shape << endl;
            }
        }
    }
    cout << "------------------------------------" << endl;
    cout << "Finished processing all image files." << endl;

    return 0;
}