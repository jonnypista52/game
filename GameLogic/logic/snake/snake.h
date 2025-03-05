#ifndef snake_h
#define snake_h

#include "../gameEngine.h"
#include <list>
#include "../../../sprites/blank.h"
#include "../../../sprites/solid.h"
#include "../../../sprites/solidRed.h"

#include "../../../input/include/Stick.h"

class SNAKE : public GAMEENGINE
{
private:
    COORDINATES Coordinatestmp;
    COORDINATES NextHead;
    COORDINATES FoodCoordinates;
    std::list<COORDINATES> snakePositions;
    STICK stick;
    bool ate;
    enum dir currentDir;
    enum dir previousDir;

    void updateHead();
    enum dir getDirectionFromStick();
    enum dir dirCheck();
    bool updateAllowed();
    bool move();
    bool IsFood();
    bool SNAKE_gameOver();

public:
    explicit SNAKE(IVGA *vga);
    ~SNAKE();

    void GameLoop() override;
};

#endif