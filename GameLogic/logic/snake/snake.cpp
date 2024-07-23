#include "./snake.h"

SNAKE::SNAKE(IVGA *vga)
{
    this->Coordinatestmp.x = 0;
    this->Coordinatestmp.y = 0;
    this->vga = vga;

    for (int i = 0; i < MAPHEIGTH; i++)
    {
        for (int j = 0; j < MAPLENGHT; j++)
        {
            this->backgroundSpritesMap[i][j] = &blank_pixel_data;
        }
    }

    snakePositions.push_front(this->Coordinatestmp);
    this->backgroundSpritesMap[0][0] = &solid_pixel_data;
    this->backgroundSpritesMap[0][1] = &solid_pixel_data;
    this->backgroundSpritesMap[0][2] = &solid_pixel_data;
    this->backgroundSpritesMap[0][19] = &solid_pixel_data;
    
    this->backgroundSpritesMap[1][19] = &solid_pixel_data;
    this->backgroundSpritesMap[2][19] = &solid_pixel_data;
    this->backgroundSpritesMap[3][19] = &solid_pixel_data;
    this->backgroundSpritesMap[4][19] = &solid_pixel_data;
    this->backgroundSpritesMap[5][19] = &solid_pixel_data;
    this->backgroundSpritesMap[6][19] = &solid_pixel_data;
    this->backgroundSpritesMap[7][19] = &solid_pixel_data;
    this->backgroundSpritesMap[8][19] = &solid_pixel_data;
    this->backgroundSpritesMap[9][19] = &solid_pixel_data;
    this->backgroundSpritesMap[10][19] = &solid_pixel_data;
    this->backgroundSpritesMap[11][19] = &solid_pixel_data;
    this->backgroundSpritesMap[12][19] = &solid_pixel_data;
    this->backgroundSpritesMap[13][19] = &solid_pixel_data;
    this->backgroundSpritesMap[14][19] = &solid_pixel_data;
    
}

SNAKE::~SNAKE()
{
}

bool SNAKE::updateAllowed()
{
    if (vga->framecounter > (uint)(this->updateStartFrame + this->updateFrameDelay))
    {
        this->updateStartFrame = vga->framecounter;
        return true;
    }
    return false;
}

// TODO just make the game
void SNAKE::GameLoop()
{
    /*
    if (updateAllowed())
    {

        // gpio_put(TESTPIN, 0);
        this->backgroundSpritesMap[this->Coordinatestmp.x][this->Coordinatestmp.y] = &blank_pixel_data;
        this->Coordinatestmp.y = (this->Coordinatestmp.y + 1) % (MAPLENGHT);
        if (this->Coordinatestmp.y == 0)
        {
            this->Coordinatestmp.x = (this->Coordinatestmp.x + 1) % (MAPHEIGTH);
        }
        this->backgroundSpritesMap[this->Coordinatestmp.x][this->Coordinatestmp.y] = &defender_pixel_data;
        // gpio_put(TESTPIN, 1);
    }
    */
}