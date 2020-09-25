#include "pixels.h"

Pixels::Pixels(){
  redColor = 0;
  greenColor = 0;
  blueColor = 0;
}

Pixels::Pixels(float redValue, float greenValue, float blueValue){
  redColor = redValue;
  greenColor = greenValue;
  blueColor = blueValue;
}

void Pixels::setRedColor(float value){
  redColor = value;
}

void Pixels::setGreenColor(float value){
  greenColor = value;
}

void Pixels::setBlueColor(float value){
  blueColor = value;
}