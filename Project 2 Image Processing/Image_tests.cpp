#include "Matrix.hpp"
#include "Image_test_helpers.hpp"
#include "unit_test_framework.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <cassert>

using namespace std;

// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Sets various pixels in a 2x2 Image and checks
// that Image_print produces the correct output.
TEST(test_print_basic) {
  Image img;
  const Pixel red = {255, 0, 0};
  const Pixel green = {0, 255, 0};
  const Pixel blue = {0, 0, 255};
  const Pixel white = {255, 255, 255};

  Image_init(&img, 2, 2);
  Image_set_pixel(&img, 0, 0, red);
  Image_set_pixel(&img, 0, 1, green);
  Image_set_pixel(&img, 1, 0, blue);
  Image_set_pixel(&img, 1, 1, white);

  // Capture our output
  ostringstream s;
  Image_print(&img, s);

  // Correct output
  ostringstream correct;
  correct << "P3\n2 2\n255\n";
  correct << "255 0 0 0 255 0 \n";
  correct << "0 0 255 255 255 255 \n";
  ASSERT_EQUAL(s.str(), correct.str());
}

TEST(test_imgfill){
  Matrix mat; 
  Image img;
  Pixel pix;
  Pixel color;
  color.r = 220;
  color.g = 34;
  color.b = 0;
  //vector<vector<int>> matrix;
  int rows = 5;
  int cols = 4;
  Image_init(&img, cols, rows);
  Image_fill(&img,color);
  pix = Image_get_pixel(&img, 3, 2);
  Image_print(&img, cout);
  //Matrix_fill_border(&mat, 4);
  ASSERT_EQUAL(pix.r, 220);
  //mat.data[4 * mat.width + 3] = 9;
  //mat.data[4 * mat.width + 2] = -1;
  //int maxi = Matrix_max(&mat);
  //int min = Matrix_fill_border(&mat, 5);
  //Matrix_print(&mat, cout);
  //cout << maxi << endl;
  //cout << min << endl;
}

TEST(test_setpix){
  Matrix mat;
  Image img;
  Pixel pix;
  Pixel color;
  color.r = 220;
  color.g = 34;
  color.b = 0;
  //vector<vector<int>> matrix;
  int rows = 5;
  int cols = 4;
  Image_init(&img, cols, rows);
  Image_set_pixel(&img, 3, 2, color);
  pix = Image_get_pixel(&img, 3, 2);
  //Matrix_fill_border(&mat, 4);
  ASSERT_EQUAL(pix.r, 220);
  ASSERT_EQUAL(pix.g, 34);
  ASSERT_EQUAL(pix.b, 0);


}

TEST(onebyoneimg){
  Image img;
  Image_init(&img, 1, 1);
  ASSERT_EQUAL(Image_width(&img), 1);
  ASSERT_EQUAL(Image_height(&img), 1);
}

TEST(onesimg){
  Image wide;
  Image_init(&wide, 8, 1);
  ASSERT_EQUAL(Image_width(&wide), 8);
  ASSERT_EQUAL(Image_height(&wide), 1);

  Image tall;
  Image_init(&tall, 1, 8);
  ASSERT_EQUAL(Image_width(&tall), 1);
  ASSERT_EQUAL(Image_height(&tall), 8);
}

TEST(teststream) {
  istringstream in("P3\n1 1\n255\n12 34 56\n");
  Image img;
  Image_init(&img, in);
  ASSERT_EQUAL(Image_width(&img), 1);
  ASSERT_EQUAL(Image_height(&img), 1);
}



// IMPLEMENT YOUR TEST FUNCTIONS HERE
// You are encouraged to use any functions from Image_test_helpers.hpp as needed.

TEST_MAIN() // Do NOT put a semicolon here
