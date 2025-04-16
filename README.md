
# Image Processing Filters

This repository contains a C++ program that implements a variety of image processing filters for grayscale and color images. The filters perform operations such as converting images to black and white, rotating, flipping, merging, applying edge detection, and more. The program reads and writes BMP images using custom libraries.

## Features

### Filters Implemented:
1. **Black & White Filter**: Converts grayscale images to black and white based on pixel values.
2. **Invert Filter**: Inverts the colors of a grayscale image.
3. **Merge Filter**: Merges two images by averaging their pixel values.
4. **Flip Filter**: Flips images either horizontally or vertically.
5. **Rotate Filter**: Rotates images by 90°, 180°, or 270°.
6. **Darken/Lighten Filter**: Adjusts the brightness of the image by darkening or lightening it.
7. **Edge Detection**: Detects edges in an image based on pixel differences.
8. **Enlarge Filter**: Enlarges a specific quadrant of the image.
9. **Shrink Filter**: Shrinks the image by a factor of 1/2, 1/3, or 1/4.
10. **Mirror Filter**: Creates a mirror image of the original, either left, right, upper, or down.
11. **Shuffle Filter**: Shuffles the quadrants of an image in a user-defined order.
12. **Blur Filter**: Applies a blur effect by averaging the surrounding pixels.
13. **Crop Filter**: Crops the image to a specific region and places it in the center.
14. **Skew (Stretch) Filters**: Skews images either horizontally or vertically by a given degree.

## Prerequisites

- C++ compiler (e.g., g++)
- BMP image files (grayscale or color)

## Setup

1. **Clone the repository**:
   ```bash
   git clone https://github.com/yourusername/image-processing-filters.git
   cd image-processing-filters
   ```

2. **Compile the code**:
   You can compile the project with `g++` (or your preferred C++ compiler). Make sure to link the necessary libraries:
   ```bash
   g++ -o image_filter image_filter.cpp -lstdc++
   ```

3. **Run the program**:
   After compiling, you can run the program:
   ```bash
   ./image_filter
   ```

4. **Load an image**:
   When prompted, provide the file path of the image you want to process (BMP format only).

## Usage

Once the program is running, you'll be presented with a menu of filter options to apply to the image. Choose an option by entering the corresponding number.

Here are the available options:
1. **Convert to Black & White**
2. **Invert Colors**
3. **Merge with Another Image**
4. **Flip Image (Horizontal/Vertical)**
5. **Rotate Image (90°/180°/270°)**
6. **Darken/Lighten Image**
7. **Edge Detection**
8. **Enlarge Image (1x, 2x, 3x, 4x)**
9. **Shrink Image (1/2, 1/3, 1/4)**
10. **Mirror Image (Left, Right, Up, Down)**
11. **Shuffle Image**
12. **Blur Image**
13. **Crop Image**
14. **Skew Image (Horizontal/Vertical)**

For each option, you may be prompted for additional information, such as file names, angles, or image portions to process.

## Libraries

The program relies on the following custom libraries:
- `bmplib.h` and `bmplib.cpp`: Libraries for reading and writing BMP images.
- `colored.cpp`: Functions specific to handling color images (optional, for color image processing).

These libraries are included in the `libraries/` folder.

## Contribution

Feel free to fork the repository and submit pull requests if you want to contribute to this project. You can add more filters or improve the existing ones.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgments

- The image processing functions are based on common algorithms for manipulating pixel values.
- Thanks to the creators of the `bmplib` for providing a useful library for reading and writing BMP images.
