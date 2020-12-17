#ifndef IMAGE_H
#define IMAGE_H

#include "pixels.h"
#include <vector>
#include <string>

class Image{
  private: 
    std::string file_name;
    std::string magic_number;
    int threshold_val;
    int cols;
    int rows;
    std::vector<std::vector<Pixels> > image_vector;

  public: 
    Image();
    Image(std::string, int, int, int);
    ~Image();
    void setFileName(std::string);
    void setMagicNumber (std::string);
    void setThresholdVal(int);
    void setCols(int);
    void setRows(int);
    int getCols();
    int getRows();

};

#endif
