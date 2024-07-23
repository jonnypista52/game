#ifndef snake_h
#define snake_h

#include "../gameEngine.h"
#include <list>
#include "../../../sprites/blank.h"
#include "../../../sprites/defender.h"
#include "../../../sprites/specialist.h"
#include "../../../sprites/solid.h"

class SNAKE : public GAMEENGINE
{
private:
    COORDINATES Coordinatestmp;
    std::list<COORDINATES> snakePositions;

public:
    explicit SNAKE(IVGA *vga);
    ~SNAKE();
    bool updateAllowed();
    void GameLoop() override;
};

#endif