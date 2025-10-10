-----

# Shape Classifier using C++

A simple command-line application written in C++ that classifies basic shapes (circles and triangles) from image files. This project performs image processing tasks from scratch, without relying on external libraries for processing, except for loading the initial image.

-----

## Prerequisites

* **Visual Studio**: Visual Studio 2019 or 2022 with the **Desktop development with C++** workload installed.
* **OpenCV**: A pre-built OpenCV library for Windows.
    * You can download it from the [official OpenCV releases page](https://opencv.org/releases/).
    * It is recommended to extract the library to a simple path, such as `C:\opencv`.

***

## Project Setup

1.  **Create a Visual Studio Project**
    * Open Visual Studio and create a new **C++ Console App** project.

2.  **Add Source Files**
    * Add the provided source files (`main.cpp`, `image.cpp`, `feature.cpp`) and header files (`image.h`, `feature.h`) to the project.

3.  **Configure Project Properties**
    * In the **Solution Explorer**, right-click the project name and go to **Properties**.
    * At the top of the window, change the **Platform** to **x64**.
    * The following settings should be configured with the **Configuration** set to **All Configurations**, unless specified otherwise.

    ---

    #### A. C/C++ Settings
    * **C/C++ > General > Additional Include Directories**:
        * Add the path to your OpenCV installation's `build\include` folder.
        * Example: `C:\opencv\build\include`

    * **C/C++ > Code Generation > Runtime Library**:
        * For **Debug** configuration: **Multi-threaded Debug DLL (/MDd)**
        * For **Release** configuration: **Multi-threaded DLL (/MD)**

    ---

    #### B. Linker Settings
    * **Linker > General > Additional Library Directories**:
        * Add the path to the `lib` folder corresponding to your Visual Studio version.
        * For VS 2019: `C:\opencv\build\x64\vc16\lib`
        * For VS 2022: `C:\opencv\build\x64\vc17\lib`

    * **Linker > Input > Additional Dependencies**:
        * Add the names of the OpenCV `.lib` files to link. (XXXX is the version number).
        ```
        opencv_worldXXXX.lib
        opencv_worldXXXXd.lib
        ```
***

## Features

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


## How to Build and Run

1.  **Clone the Repository**:

    ```bash
    git clone <your-repository-url>
    cd <your-repository-directory>
    ```

2. **Prepare Input Images**

* Prepare the input image files (1.jpg, 2.jpg, 3.jpg, 4.jpg).

* Copy these files into the main project folder (the one containing the .vcxproj file).

3. **Copy DLL Files**

* Navigate to the bin folder of your OpenCV installation (e.g., C:\opencv\build\x64\vc16\bin).

* Copy the opencv_worldXXXX.dll and opencv_worldXXXXd.dll files.

* Paste them into the project's build output folder (e.g., YourProjectFolder\x64\Release).

4. **Build and Run**

* In the Visual Studio toolbar, set the build configuration to Release | x64.

* Press Ctrl+F5 or go to Debug > Start Without Debugging to run the program.

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