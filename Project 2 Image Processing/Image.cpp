#include <cassert>
#include "Image.hpp"
using namespace std;

// REQUIRES: img points to an Image
//           0 < width && 0 < height
// MODIFIES: *img
// EFFECTS:  Initializes the Image with the given width and height, with
//           all pixels initialized to RGB values of 0.
void Image_init(Image* img, int width, int height) {
  img->width = width;
  img->height = height;
  Matrix_init(&img->red_channel, img->width, img->height);
  Matrix_init(&img->green_channel, img->width, img->height);
  Matrix_init(&img->blue_channel, img->width, img->height);


  // TODO Replace with your implementation!
}

// REQUIRES: img points to an Image
//           is contains an image in PPM format without comments
//           (anqy kind of whitespace is ok)
// MODIFIES: *img, is
// EFFECTS:  Initializes the Image by reading in an image in PPM format
//           from the given input stream.
// NOTE:     See the project spec for a discussion of PPM format.
void Image_init(Image* img, std::istream& is) {
  string ignore;
  int r;
  int g;
  int b;
  int width;
  int height;
  is >> ignore >> width >> height >> ignore;
  Image_init(img, width, height);
  for (int row = 0; row < height; ++row){
    for (int col = 0; col < width; ++col){
      is >> r >> g >> b;
      Image_set_pixel(img, row, col, Pixel{r,g,b});
    }

  }

      
  
  

   // TODO Replace with your implementation!
}

// REQUIRES: img points to a valid Image
// MODIFIES: os
// EFFECTS:  Writes the image to the given output stream in PPM format.
//           You must use the kind of whitespace specified here.
//           First, prints out the header for the image like this:
//             P3 [newline]
//             WIDTH [space] HEIGHT [newline]
//             255 [newline]
//           Next, prints out the rows of the image, each followed by a
//           newline. Each pixel in a row is printed as three ints
//           for its red, green, and blue components, in that order. Each
//           int is followed by a space. This means that there will be an
//           "extra" space at the end of each line. See the project spec
//           for an example.
void Image_print(const Image* img, std::ostream& os) {
  
  os << "P3" << endl << img->width << " " << img->height << endl << "255" << endl;

  for (int row = 0; row < img->height; ++row){
    for (int col = 0; col < img->width; ++ col){
      os << *Matrix_at(&img->red_channel, row, col) << " ";
      os << *Matrix_at(&img->green_channel, row, col) << " ";
      os << *Matrix_at(&img->blue_channel, row, col) << " ";
    }
    os << endl;
  }

    // TODO Replace with your implementation!
}

// REQUIRES: img points to a valid Image
// EFFECTS:  Returns the width of the Image.
int Image_width(const Image* img) {
  
  return img->width; // TODO Replace with your implementation!
}

// REQUIRES: img points to a valid Image
// EFFECTS:  Returns the height of the Image.
int Image_height(const Image* img) {
  
  return img->height; // TODO Replace with your implementation!
}

// REQUIRES: img points to a valid Image
//           0 <= row && row < Image_height(img)
//           0 <= column && column < Image_width(img)
// EFFECTS:  Returns the pixel in the Image at the given row and column.
Pixel Image_get_pixel(const Image* img, int row, int column) {
  
  Pixel pix;
 
  // pix.r = img->red_channel.data[row * img->width + column];
  // pix.g = img->green_channel.data[row * img->width + column];
  // pix.b = img->blue_channel.data[row * img->width + column];
  
  pix.r = *Matrix_at(&img->red_channel, row, column);
  pix.g = *Matrix_at(&img->green_channel, row, column);
  pix.b = *Matrix_at(&img->blue_channel, row, column);
    
  return pix;
   // TODO Replace with your implementation!
}

// REQUIRES: img points to a valid Image
//           0 <= row && row < Image_height(img)
//           0 <= column && column < Image_width(img)
// MODIFIES: *img
// EFFECTS:  Sets the pixel in the Image at the given row and column
//           to the given color.
void Image_set_pixel(Image* img, int row, int column, Pixel color) {
  *Matrix_at(&img->red_channel, row, column) = color.r;
  *Matrix_at(&img->green_channel, row, column) = color.g;
  *Matrix_at(&img->blue_channel, row, column) = color.b;

   // TODO Replace with your implementation!
}

// REQUIRES: img points to a valid Image
// MODIFIES: *img
// EFFECTS:  Sets each pixel in the image to the given color.
void Image_fill(Image* img, Pixel color) {
  
  for (int row = 0; row < img->height; ++row){
    for (int col = 0; col < img->width; ++ col){
      *Matrix_at(&img->red_channel, row, col) = color.r;
      *Matrix_at(&img->green_channel, row, col) = color.g;
      *Matrix_at(&img->blue_channel, row, col) = color.b;
    }

  }
   // TODO Replace with your implementation!
}
