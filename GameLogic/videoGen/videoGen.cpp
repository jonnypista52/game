#include "./videoGen.h"

VideoGen::VideoGen(VGA *vga)
{
    this->vga = vga;
    for(int i=0;i<MAPLENGHT;i++){
        for(int j=0;j<MAPHEIGTH;j++){
            mapBgSpritePointer[i][j] = &caster_pixel_data;
        }
    }
}

VideoGen::~VideoGen()
{
    delete vga;
}

void VideoGen::drawbgLine()
{
}


