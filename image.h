#ifndef IMAGE_H
#define IMAGE_H

#include "pixels.h"
#include <vector>
#include <string>

class Image{
  private: 
    std::string file_name;
    const std::string magic_number = "P3";
    const int threshold_val = 255;
    int cols;
    int rows;
    std::vector<std::vector<Pixels> > image_vector;

  public: 
    Image();
    Image(std::string, int, int, int);
    ~Image();
    void setFileName(std::string);
    void setCols(int);
    void setRows(int);
    int getCols();
    int getRows();
};

#endif
