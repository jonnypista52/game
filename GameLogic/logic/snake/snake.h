#ifndef snake_h
#define snake_h

#include "../gameEngine.h"
#include <list>
#include "../../../sprites/blank.h"
#include "../../../sprites/supporter.h"
#include "../../../sprites/specialist.h"

class SNAKE : public GAMEENGINE
{
private:
    COORDINATES Coordinatestmp;
    std::list<COORDINATES> snakePositions;

public:
    explicit SNAKE(IVGA *vga);
    ~SNAKE();
    void GameLoop() override;
    void fill_Bg_Sprites() override;
};

#endif