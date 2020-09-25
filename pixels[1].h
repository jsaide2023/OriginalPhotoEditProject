#ifndef PIXEL_H
#define PIXEL_H

class Pixels{
  private:
    float redColor;
    float greenColor;
    float blueColor;

  public:
    Pixels();
    Pixels(float, float, float);
    
    void setRedColor(float);
    void setGreenColor(float);
    void setBlueColor(float); 

};

#endif