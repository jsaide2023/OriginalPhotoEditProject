#ifndef IMAGE_H
#define IMAGE_H

#include "pixels.h"
#include <vector>
#include <string>

class Image{
  private: 
    std::string file_name;
    std::string magic_number = "P3";
    int threshold_val;
    int cols;
    int rows;
  //2-D vector better choice than dynamic 2d array
    std::vector<std::vector<Pixels> > image_vector;

  public:
  //FIXME: figure out what functions can be applied here as in crop row, columns etc. 
    Image();
    Image(std::string, int, int, int);
    ~Image();
    void setFileName(std::string);
    void setMagicNumber (std::string);
    void setThresholdVal(int);
    void setCols(int);
    void setRows(int);

};

#endif
