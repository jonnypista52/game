#ifndef videoGen_h
#define videoGen_h

#include "../../vga/vga.h"
#include "../../sprites/caster.h"

class VideoGen
{
private:
    unsigned char(*mapBgSpritePointer[MAPLENGHT][MAPHEIGTH])[32][32];
    VGA *vga;

public:
    VideoGen(VGA *vga);
    ~VideoGen();
};

#endif