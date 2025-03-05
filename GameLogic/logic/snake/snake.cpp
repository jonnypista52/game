#include "./snake.h"

SNAKE::SNAKE(IVGA *vga)
{
    this->stick = STICK();
    this->vga = vga;
    currentDir = right;
    previousDir = right;
    NextHead.x = 5;
    NextHead.y = 4;
    ate = false;
    for (int i = 0; i < MAPHEIGTH; i++)
    {
        for (int j = 0; j < MAPLENGHT; j++)
        {
            this->backgroundSpritesMap[i][j] = &blank_pixel_data;
        }
    }
    // put food down
    this->FoodCoordinates.x = 1;
    this->FoodCoordinates.y = 1;
    this->backgroundSpritesMap[1][1] = &solid_red_pixel_data;

    this->Coordinatestmp.x = 2;
    this->Coordinatestmp.y = 4;
    snakePositions.push_front(this->Coordinatestmp);
    this->Coordinatestmp.x = 2;
    this->Coordinatestmp.y = 4;
    snakePositions.push_front(this->Coordinatestmp);
    this->Coordinatestmp.x = 4;
    this->Coordinatestmp.y = 4;
    snakePositions.push_front(this->Coordinatestmp);

    this->backgroundSpritesMap[2][4] = &solid_pixel_data;
    this->backgroundSpritesMap[3][4] = &solid_pixel_data;
    this->backgroundSpritesMap[4][4] = &solid_pixel_data;
}

SNAKE::~SNAKE()
{
}

enum dir SNAKE::getDirectionFromStick()
{

    STICK_POSITION tmp;
    tmp = this->stick.getStickPosition();

    if (tmp.x > STICK_binary_treshold)
        return up;
    if (tmp.y > STICK_binary_treshold)
        return right;
    // convert negative to positive, if it would been a big pistivite value then it
    // would have already exited
    if ((tmp.x * -1) > STICK_binary_treshold)
        return down;
    if ((tmp.y * -1) > STICK_binary_treshold)
        return left;
    return none;
}

enum dir SNAKE::dirCheck()
{
    if (currentDir != previousDir)
    {
        switch (previousDir)
        {
        case up: // if up, then disable up and down
            if (currentDir == up || currentDir == down)
            {
                return previousDir;
            }
            break;
        case down: // if down disable up/down
            if (currentDir == up || currentDir == down)
            {
                return previousDir;
            }
            break;
        case left: // if left disable left/right
            if (currentDir == left || currentDir == right)
            {
                return previousDir;
            }
            break;
        case right: // if right disable left/right
            if (currentDir == left || currentDir == right)
            {
                return previousDir;
            }
            break;
        default:
            printf("not supposed to happen");
        }
    }
    return currentDir;
}

void SNAKE::updateHead()
{
    switch (currentDir)
    {
    case up:
        NextHead.x--;
        break;
    case down:
        NextHead.x++;
        break;
    case left:
        NextHead.y--;
        break;
    case right:
        NextHead.y++;
        break;
    default:
        printf("not supposed to happen");
    }
}

bool SNAKE::move()
{
    if (SNAKE_gameOver())
        return false;

    snakePositions.push_front(this->NextHead);
    this->backgroundSpritesMap[NextHead.x][NextHead.y] = &solid_pixel_data;

    // remove tail if not ate anything
    if (!ate)
    {
        COORDINATES tmp = snakePositions.back();
        this->backgroundSpritesMap[tmp.x][tmp.y] = &blank_pixel_data;
        snakePositions.pop_back();
    }
    return true;
}

bool SNAKE::IsFood()
{
    if (this->backgroundSpritesMap[NextHead.x][NextHead.y] == &solid_red_pixel_data)
    {
        return true;
    }
    return false;
}

bool SNAKE::SNAKE_gameOver()
{

    // boundy
    if (NextHead.x < 0 || NextHead.y < 0 || NextHead.x >= MAPLENGHT || NextHead.y >= MAPHEIGTH)
        return true;

    // yooo, that's not possible
    if (this->backgroundSpritesMap[NextHead.y][NextHead.y] == &solid_pixel_data)
    {
        return true;
    }

    return false;
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

    if (updateAllowed())
    {
        // gpio_put(TESTPIN, 0);
        currentDir = getDirectionFromStick();
        if (currentDir == none)
            currentDir = previousDir;
        // printf("dir: %i\n", currDir);
        currentDir = dirCheck();
        updateHead();
        IsFood();
        move(); // it will just auto freeze when the game ends

        // gpio_put(TESTPIN, 1);
    }
}