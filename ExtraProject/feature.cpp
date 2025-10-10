#include "feature.h"
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Calculate perimeter
static double computePerimeter(const std::vector<MyPoint>& contour) {
    double perim = 0.0;
    if (contour.size() < 2) return 0.0;
    for (size_t i = 0; i < contour.size(); i++) {
        MyPoint p1 = contour[i];
        MyPoint p2 = contour[(i + 1) % contour.size()];
        perim += std::sqrt(std::pow(p2.x - p1.x, 2) + std::pow(p2.y - p1.y, 2));
    }
    return perim;
}

// Calculate area (Shoelace formula)
static double computeArea(const std::vector<MyPoint>& contour) {
    double area = 0.0;
    if (contour.size() < 3) return 0.0;
    for (size_t i = 0; i < contour.size(); i++) {
        MyPoint p1 = contour[i];
        MyPoint p2 = contour[(i + 1) % contour.size()];
        area += (p1.x * p2.y - p2.x * p1.y);
    }
    return std::fabs(area) / 2.0;
}

// Extract features
ShapeFeature extractFeatures(const std::vector<MyPoint>& contour) {
    ShapeFeature feat;
    feat.perimeter = computePerimeter(contour);
    feat.area = computeArea(contour);

    if (feat.perimeter > 0) {
        feat.circularity = (4 * M_PI * feat.area) / (feat.perimeter * feat.perimeter);
    }
    else {
        feat.circularity = 0;
    }

    return feat;
}

// Classify shape
std::string classifyShape(const ShapeFeature& feat) {
    if (feat.circularity > 0.8) {
        return "Circle";
    }
    else {
        return "Triangle";
    }
}