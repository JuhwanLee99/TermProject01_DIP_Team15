-----

# Shape Classifier using C++

A simple command-line application written in C++ that classifies basic shapes (circles and triangles) from image files. This project performs image processing tasks from scratch, without relying on external libraries for processing, except for loading the initial image.

-----

## \#\# Features

  * **Image Loading**: Loads `.jpg` images using the OpenCV library.
  * **Manual Image Processing**: Implements all processing steps manually, including:
      * Grayscale Conversion
      * Binarization (Thresholding)
      * Contour Tracing (Moore-Neighbor Tracing Algorithm)
  * **Feature Extraction**: Calculates geometric features of a shape, such as:
      * Perimeter
      * Area (using the Shoelace formula)
      * Circularity
  * **Shape Classification**: Classifies shapes as "Circle" or "Triangle" based on the calculated circularity score.

-----

## \#\# Prerequisites

  * A C++ compiler that supports C++11 or newer (e.g., GCC, Clang, MSVC).
  * **OpenCV**: This library is required *only* for loading images. Ensure it is installed on your system.

-----

## \#\# How to Build and Run

1.  **Clone the Repository**:

    ```bash
    git clone <your-repository-url>
    cd <your-repository-directory>
    ```

2.  **Compile the Code**:
    You need to link the OpenCV libraries during compilation. The following is an example command using `g++`.

    ```bash
    g++ main.cpp image.cpp feature.cpp -o shape_classifier $(pkg-config --cflags --libs opencv4)
    ```

    *Note: If your OpenCV version is different, you might need to change `opencv4` to the appropriate name (e.g., `opencv`).*

3.  **Run the Application**:
    Make sure the image files (`1.jpg` for a circle, `2.jpg` for a triangle) are in the same directory as the executable.

    ```bash
    ./shape_classifier
    ```

-----

## \#\# Expected Output

After running the program, you should see the classification results printed to the console:

```
1.jpg → Circle
2.jpg → Triangle
```

-----

## \#\# Code Structure

  * `main.cpp`: The main entry point of the application. It orchestrates the image processing pipeline and prints the final results.
  * `image.h` / `image.cpp`: Contains all functions related to image manipulation, including loading, grayscale conversion, binarization, and contour extraction.
  * `feature.h` / `feature.cpp`: Contains all functions related to geometric feature calculation and shape classification logic.
  * `1.jpg`: An sample image of a circle.
  * `2.jpg`: A sample image of a triangle.