#include "Image.h"

using namespace std;
using namespace cs225;

void Image::lighten(){
    for(unsigned x = 0; x < this->width(); x++){
        for(unsigned y = 0; y < this->height(); y++){
            HSLAPixel &pixel = this->getPixel(x, y);
            pixel.l = pixel.l + 0.1;
            if (pixel.l > 1){
                pixel.l = 1;
            }
        }
    }
}
        
void Image::lighten(double amount){
    for(unsigned x = 0; x < this->width(); x++){
        for(unsigned y = 0; y < this->height(); y++){
            HSLAPixel &pixel = this->getPixel(x, y);
            pixel.l = pixel.l + amount;
            if (pixel.l > 1){                          // keep under 1
                pixel.l = 1;
            }
        }
    }
}

void Image::darken(){
    for(unsigned x = 0; x < this->width(); x++){
        for(unsigned y = 0; y < this->height(); y++){
            HSLAPixel &pixel = this->getPixel(x, y);
            pixel.l = pixel.l - 0.1;
            if (pixel.l < 0){                          //keep above 0
                pixel.l = 0;
            }
        }
    }
}    

void Image::darken(double amount){
    for(unsigned x = 0; x < this->width(); x++){
        for(unsigned y = 0; y < this->height(); y++){
            HSLAPixel &pixel = this->getPixel(x, y);
            pixel.l = pixel.l - amount;
            if (pixel.l < 0){
                pixel.l = 0;
            }
        }
    }
}    

void Image::saturate(){
    for(unsigned x = 0; x < this->width(); x++){
        for(unsigned y = 0; y < this->height(); y++){
            HSLAPixel &pixel = this->getPixel(x, y);
            pixel.s = pixel.s + 0.1;
            if (pixel.s > 1){
                pixel.s = 1;
            }
        }
    }
}    

void Image::saturate(double amount){
    for(unsigned x = 0; x < this->width(); x++){
        for(unsigned y = 0; y < this->height(); y++){
            HSLAPixel &pixel = this->getPixel(x, y);
            pixel.s = pixel.s + amount;
            if (pixel.s > 1){
                pixel.s = 1;
            }
        }
    }
}    

void Image::desaturate(){
    for(unsigned x = 0; x < this->width(); x++){
        for(unsigned y = 0; y < this->height(); y++){
            HSLAPixel &pixel = this->getPixel(x, y);
            pixel.s = pixel.s - 0.1;
            if (pixel.s < 0){
                pixel.s = 0;
            }
        }
    }
}    

void Image::desaturate(double amount){
    for(unsigned x = 0; x < this->width(); x++){
        for(unsigned y = 0; y < this->height(); y++){
            HSLAPixel &pixel = this->getPixel(x, y);
            pixel.s = pixel.s - amount;
            if (pixel.s < 0){
                pixel.s = 0;
            }
        }
    }
}    

void Image::grayscale(){
    for(unsigned x = 0; x < this->width(); x++){
        for(unsigned y = 0; y < this->height(); y++){
            HSLAPixel &pixel = this->getPixel(x, y);
            pixel.s = 0;
        }
    }
}

void Image::rotateColor(double degrees){
    for(unsigned x = 0; x < this->width(); x++){
        for(unsigned y = 0; y < this->height(); y++){
            HSLAPixel &pixel = this->getPixel(x, y);
            pixel.h = pixel.h + degrees;
            if (pixel.h > 360){
                pixel.h = pixel.h - 360;
            }
            if (pixel.h < 0){
                pixel.h = pixel.h + 360;
            }
        }
    }
}

void Image::illinify(){
    for(unsigned x = 0; x < this->width(); x++){
        for(unsigned y = 0; y < this->height(); y++){
            HSLAPixel &pixel = this->getPixel(x, y);
            if(pixel.h < 293.5 && pixel.h > 113.5){
                pixel.h = 216;
            }
            else{
                pixel.h = 11;
            }
        }
    }
}

void Image::scale(double factor){
    unsigned nw = this->width() * factor;
    unsigned nh = this->height() * factor;
    PNG* temp = new PNG (nw, nh);                                          //need temporary object to load into "this" or else SIGABRT error
    for (unsigned x = 0; x < nw; x++){
        for (unsigned y = 0; y < nh; y++){
            temp->getPixel(x, y).h = this->getPixel(x/factor, y/factor).h;
            temp->getPixel(x, y).s = this->getPixel(x/factor, y/factor).s;
            temp->getPixel(x, y).l = this->getPixel(x/factor, y/factor).l;
            temp->getPixel(x, y).a = this->getPixel(x/factor, y/factor).a;
        }
    }
    this->resize(nw, nh);
      for (unsigned x = 0; x < nw; x++){
          for (unsigned y = 0; y < nh; y++){
              this->getPixel(x,y).h = temp->getPixel(x,y).h;
              this->getPixel(x,y).s = temp->getPixel(x,y).s;
              this->getPixel(x,y).l = temp->getPixel(x,y).l;
              this->getPixel(x,y).a = temp->getPixel(x,y).a;
          }
      }
      delete temp;
  }
void Image::scale(unsigned w, unsigned h){
    double nw = (double) w / this->width();
    double nh = (double) h / this->height();
    if(nw < nh){
      scale(nw);
    }
    else{
        scale(nh);
  }
}