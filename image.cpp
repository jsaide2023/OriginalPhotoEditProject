#include "image.h"

Image::Image() {
  file_name = "";
  threshold_val = 255;
  cols = 0;
  rows = 0;
}

Image::Image(std::string filename, int thresh_val, int num_cols, int num_rows) {
  file_name = filename;
  threshold_val = thresh_val;
  cols = num_cols;
  rows = num_rows;

  image_vector.resize(num_rows);
  for (int i = 0; i < num_rows; i++) {
    image_vector[i].resize(num_cols);
  }

}
Image::~Image() {} //figure out how to implent or if to implement a destructor
void Image::setFileName(std::string filename) {
  file_name = filename;
}
void Image::setMagicNumber (std::string magic_num) {
  magic_number = magic_num;
}
void Image::setThresholdVal(int thresh_val) {
  threshold_val = thresh_val;
}
void Image::setCols(int num_cols) {
  cols = num_cols;
}
void Image::setRows(int num_rows) {
  rows = num_rows;
}


