#ifndef snake_h
#define snake_h

#include "../gameEngine.h"
#include <list>
#include "../../../sprites/blank.h"
#include "../../../sprites/defender.h"
#include "../../../sprites/specialist.h"
#include "../../../sprites/solid.h"

#include "../../../input/include/Stick.h"

class SNAKE : public GAMEENGINE
{
private:
    COORDINATES Coordinatestmp;
    std::list<COORDINATES> snakePositions;
    uint8_t direction; //0 up, 1 right, 2 down, 3 left
    STICK stick;

public:
    explicit SNAKE(IVGA *vga);
    ~SNAKE();
    uint8_t getDirectionFromStick();
    bool updateAllowed();
    void GameLoop() override;
};

#endif