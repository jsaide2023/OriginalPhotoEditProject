#include "image.h"

Image::Image() {
  file_name = "";
  cols = 0;
  rows = 0;
}

Image::Image(std::string filename, int num_cols, int num_rows) {
  file_name = filename;
  cols = num_cols;
  rows = num_rows;

  image_vector.resize(num_rows);
  for (int i = 0; i < num_rows; i++) {
    image_vector[i].resize(num_cols);
  }
}

Image::~Image() {
  //use destructor to set object to its original state
  for (int i = 0; i < image_vector.size(); i++) {
    image_vector[i].clear();
  }
  image_vector.clear();
  cols = 0;
  rows = 0;
  file_name = "";
}
void Image::setFileName(std::string filename) {
  file_name = filename;
}
void Image::setCols(int num_cols) {
  cols = num_cols;
}
void Image::setRows(int num_rows) {
  rows = num_rows;
}
int Image::getCols() {
  return cols;
}
int Image::getRows() {
  return rows;
}
