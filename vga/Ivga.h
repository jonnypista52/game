#ifndef ivga_h
#define ivga_h

#include "../Global.h"
#include <stdlib.h>
#include <stdio.h>

class IVGA
{
private:
public:
    virtual ~IVGA() {}
    inline static int8_t doneLine = 0;     // index of buffer line in sending
    inline static int currentLineSend = 0; // scancode line
    inline static uint framecounter = 0;
    inline static uint8_t blankLine[NUM_PIXELS_INLINE]{0};
    inline static uint8_t genBuffer[BUFFER_LINE_SIZE][NUM_PIXELS_INLINE]{0};

    // sends the next data line
    virtual void sendNextLine() = 0;
    // sends an blank black line
    virtual void sendBlank() = 0;

    virtual void enablePIO() = 0;

    //! TEST
    // implement as you wish
    virtual void fill() = 0;
    // implement as you wish
    virtual void fillDifferent() = 0;
};

#endif