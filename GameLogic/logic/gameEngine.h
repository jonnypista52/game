#ifndef gameEngine_h
#define gameEngine_h

#include "../../Global.h"
#include "../../vga/Ivga.h"

struct COORDINATES
{
    uint16_t x; // -> left right
    uint16_t y; // V up down
};

class GAMEENGINE
{
protected:
    int bg_generated_line = 0;
    int bg_generated_line_buffer = 0;
    unsigned char (*backgroundSpritesMap[(MAPHEIGTH)][(MAPLENGHT)])[BGSPRITES_SIZE][BGSPRITES_SIZE];
    IVGA *vga;
public:
    virtual ~GAMEENGINE(){
        delete vga;
    };
    virtual void GameLoop() = 0;
    virtual void fill_Bg_Sprites() = 0;
};

#endif