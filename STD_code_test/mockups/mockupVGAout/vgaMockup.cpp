#include "./vgaMockup.h"

void vgaMockup::sendNextLine()
{
    std::cout << "line: " << (int)doneLine << std::endl;
    for (int i = 0; i < NUM_PIXELS_INLINE; i++)
    {
        std::cout << (int)genBuffer[doneLine][i] << " ";
    }
    std::cout << std::endl
              << std::endl;
    doneLine = (doneLine + 1) % BUFFER_LINE_SIZE;
}

void vgaMockup::sendBlank()
{
}

void vgaMockup::fill()
{
    for (int i = 0; i < BUFFER_LINE_SIZE; i++)
    {
        for (int j = 0; j < NUM_PIXELS_INLINE; j++)
        {
            genBuffer[i][j] = 0xD7;
        }
    }
}

void vgaMockup::fillDifferent()
{
    for (int i = 0; i < BUFFER_LINE_SIZE; i++)
    {
        for (int j = 0; j < NUM_PIXELS_INLINE; j += 8)
        {
            /*
            genBuffer[i][j+0] = 0x00;
            genBuffer[i][j+1] = 0x07;
            genBuffer[i][j+2] = 0x70;
            genBuffer[i][j+3] = 0x77;
            genBuffer[i][j+4] = 0x00;
            genBuffer[i][j+5] = 0xF0;
            genBuffer[i][j+6] = 0xF7;
            genBuffer[i][j+7] = 0xFF;
            */
            genBuffer[i][j + 0] = 0x00;
            genBuffer[i][j + 1] = 0xFF;
            genBuffer[i][j + 2] = 0x00;
            genBuffer[i][j + 3] = 0xFF;
            genBuffer[i][j + 4] = 0x00;
            genBuffer[i][j + 5] = 0xFF;
            genBuffer[i][j + 6] = 0x00;
            genBuffer[i][j + 7] = 0xFF;
        }
    }
}