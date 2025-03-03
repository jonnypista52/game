#include "./snake.h"

SNAKE::SNAKE(IVGA *vga)
{
    this->stick = STICK();
    this->vga = vga;

    for (int i = 0; i < MAPHEIGTH; i++)
    {
        for (int j = 0; j < MAPLENGHT; j++)
        {
            this->backgroundSpritesMap[i][j] = &blank_pixel_data;
        }
    }
    this->direction = 1;
    this->Coordinatestmp.x = 4;
    this->Coordinatestmp.y = 3;
    snakePositions.push_front(this->Coordinatestmp);
    this->Coordinatestmp.x = 4;
    this->Coordinatestmp.y = 4;
    snakePositions.push_front(this->Coordinatestmp);
    this->Coordinatestmp.x = 4;
    this->Coordinatestmp.y = 5;
    snakePositions.push_front(this->Coordinatestmp);

    this->backgroundSpritesMap[4][3] = &solid_pixel_data;
    this->backgroundSpritesMap[4][4] = &solid_pixel_data;
    this->backgroundSpritesMap[4][5] = &solid_pixel_data;
}

SNAKE::~SNAKE()
{
}

uint8_t SNAKE::getDirectionFromStick()
{

    STICK_POSITION tmp;
    tmp = this->stick.getStickPosition();

    if (tmp.x > STICK_binary_treshold)
        return 0;
    if (tmp.y > STICK_binary_treshold)
        return 1;
    //convert negative to positive, if it would been a big pistivite value then it
    //would have already exited
    if ((tmp.x * -1) > STICK_binary_treshold) 
        return 2;
    if ((tmp.x * -1) > STICK_binary_treshold)
        return 3;
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