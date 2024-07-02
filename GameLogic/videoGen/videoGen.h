#ifndef videoGen_h
#define videoGen_h

#include "../../Global.h"
#include "../../vga/vga.h"
#include "../../sprites/caster.h"
#include "../../sprites/defender.h"
#include "../../sprites/guard.h"
#include "../../sprites/medic.h"
#include "../../sprites/sniper.h"
#include "../../sprites/specialist.h"
#include "../../sprites/supporter.h"
#include "../../sprites/vanguard.h"

class VideoGen
{
private:
    int bg_generated_line = 0;
    unsigned char (*backgroundSpritesMap[MAPLENGHT][MAPHEIGTH])[BGSPRITES_SIZE][BGSPRITES_SIZE];
    IVGA *vga;
public:
    VideoGen(IVGA *vga);
    ~VideoGen();

    void random_Bg_Sprites_init(int nrOfSprites);
    void fill_Bg_Sprites();
};

#endif