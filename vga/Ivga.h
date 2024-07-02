#ifndef ivga_h
#define ivga_h

#include <stdlib.h>
#include <stdio.h>

#define BUFFER_LINE_SIZE 96
#define NUM_PIXELS_INLINE 640
class IVGA
{
private:
public:
    inline static int8_t doneLine = 0;     // index of buffer line in sending
    inline static int currentLineSend = 0; // scancode line

    inline static uint8_t blankLine[NUM_PIXELS_INLINE]{0};
    inline static uint8_t genBuffer[BUFFER_LINE_SIZE][NUM_PIXELS_INLINE]{0};

    // sends the next data line
    virtual void sendNextLine() = 0;
    // sends an blank black line
    virtual void sendBlank() = 0;

    //! TEST
    // implement as you wish
    virtual void fill() = 0;
    // implement as you wish
    virtual void fillDifferent() = 0;
};

#endif