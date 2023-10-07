#include "StickerSheet.h"
#include "Image.h"


using namespace std;
using namespace cs225;

StickerSheet::StickerSheet(const Image &picture, unsigned max){          //initialize
    maximum = max;
    sticker_ct = 0;
    stickers = new Image*[maximum];
    this->base = new Image(picture);
    xCoord = new int[maximum];
    yCoord = new int[maximum];
    for(unsigned x = 0; x < maximum; x++){
        stickers[x] = NULL;
        xCoord[x] = 0;
        yCoord[x] = 0;
    }
    
}

StickerSheet::~StickerSheet(){
    clear();

}

void StickerSheet::clear(){
    for(unsigned x = 0; x < maximum; x++){
        if(stickers[x] != NULL){
        delete stickers[x];
        stickers[x] = NULL;
        }
    }
    delete[] stickers;
    delete[] xCoord;
    delete[] yCoord;
    delete base;
}

void StickerSheet::copy(const StickerSheet & other){
    sticker_ct = other.sticker_ct;
    maximum = other.maximum;
    stickers = new Image*[maximum];
    xCoord = new int[maximum];
    yCoord = new int[maximum];
    base = new Image(*(other.base));
    for(unsigned x = 0; x < maximum; x++){
        if (other.stickers[x] == NULL){
            stickers[x] = NULL;
            xCoord[x] = other.xCoord[x];
            yCoord[x] = other.yCoord[x];
        }
        else {
            stickers[x] = new Image(*(other.stickers[x]));
        }
    }
}

StickerSheet::StickerSheet(const StickerSheet & other) {
    copy(other);
  }

const StickerSheet& StickerSheet::operator=(const StickerSheet &other){
    if(this != &other){
    clear();
    copy(other);
    }
    return *this;
}

void StickerSheet::changeMaxStickers(unsigned max){
    if(max == maximum){
        return;
    }
    Image *newbase = new Image(*base);
    Image **newstickers = new Image*[max];
    int *x2 = new int[max];
    int *y2 = new int[max];
    unsigned newct = 0;
    if(maximum < max){
        for(unsigned x = 0; x < max; x++){
            newstickers[x] = NULL;
        }
        for(unsigned y = 0; y < sticker_ct; y++){
            if(stickers[y] != NULL){
                newstickers[y] = new Image(*stickers[y]);
                x2[y] = xCoord[y];
                y2[y] = yCoord[y];
            }
        }
    }
    else{
        for(unsigned k = max; k < maximum; k++){
            removeSticker(k);
        }
    }
}

int StickerSheet::addSticker(Image &sticker, int x, int y){
    if(sticker_ct < maximum){
        for(unsigned i = 0; i < maximum; i++){
            if(stickers[i] == NULL){
                stickers[i] = new Image(sticker);
                xCoord[i] = x;
                yCoord[i] = y;
                sticker_ct++;
                return i;
            }
            
        }
    }
    return -1;

}

int StickerSheet::setStickerAtLayer(Image &sticker, unsigned layer, int x, int y){
    if(layer >= maximum || layer < 0){             //layer doesn't exist
    return -1;
    }
        stickers[layer] = new Image(sticker);
        xCoord[layer] = x;
        yCoord[layer] = y;
        return layer;
    }


bool StickerSheet::translate(unsigned index, int x, int y){
    if(stickers[index] == NULL || index >= maximum || index < 1){
        return false;
    }
        xCoord[index] = x;
        yCoord[index] = y;
        return true;
    }


void StickerSheet::removeSticker(unsigned index){
    if(stickers[index] != NULL && index < maximum){                //if there is a sticker at the given layer index, remove sticker
        delete stickers[index];
        stickers[index] = NULL;
        xCoord[index] = 0;
        yCoord[index] = 0;
    }
    else{
        return;
    }
}

Image * StickerSheet::getSticker(unsigned index){
    if(stickers[index] == NULL || index >= maximum){
        return NULL;
    }
   
        return stickers[index];
    }


int StickerSheet::layers() const{
 /*   int layers;
    for(x = 0; x < maximum; x++){             //want to see how many layers are still available (maximum - occupied layers)???
        if(stickers[x] != NULL){
            layers++;
        }
    }
    int available = maximum - layers
*/

return maximum;

}

Image StickerSheet::render() const{
    unsigned xwidth = base->width();
    unsigned yheight = base->height();
    unsigned newx;
    unsigned newy;
    for(unsigned x = 0; x < maximum; x++){
        if(stickers[x] != NULL){                                                     
            newx = stickers[x]->width() + xCoord[x];
            newy = stickers[x]->height() + yCoord[x];
            if(newx > xwidth){
                xwidth = newx;
            }
            if(newy > yheight){
                yheight = newy;
            }
        }
    }
        Image *output = new Image(*base);
        output->resize(xwidth,yheight);

        for(unsigned a = 0; a < maximum; a++){
            if(stickers[a] != NULL){
                Image temporary = *stickers[a];
                for(unsigned b = xCoord[a]; b < (xCoord[a] + temporary.width()); b++){
                    for (unsigned c = yCoord[a]; c < (yCoord[a] + temporary.height()); c++) {
                        HSLAPixel &pixel = output->getPixel(a,b);
                        HSLAPixel &pix = temporary.getPixel(b - xCoord[a], c - yCoord[a]);
                        if(pixel.a != 0){                                                           //If the alpha channel is non-zero, a pixel is drawn
                            pixel.h = pix.h;
                            pixel.s = pix.s;
                            pixel.l = pix.l;
                            pixel.a = pix.a;
                        }
                    }
                }
            }
        }
        Image final = *output;
        delete output;
        return final;
}

