#pragma once
#include <vector>
#include <string>
#include "image.h"

struct ShapeFeature {
    double area;
    double perimeter;
    double circularity;
};

ShapeFeature extractFeatures(const std::vector<MyPoint>& contour);
std::string classifyShape(const ShapeFeature& feat);