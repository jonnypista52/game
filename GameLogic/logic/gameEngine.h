#ifndef gameEngine_h
#define gameEngine_h

#include "../../Global.h"
#include "../../vga/Ivga.h"

struct COORDINATES
{
    uint16_t x; // -> left right
    uint16_t y; // V up down
};

class GAMEENGINE
{
protected:
    int bg_generated_line = 0;
    int bg_generated_line_buffer = 0;
    unsigned char (*backgroundSpritesMap[(MAPHEIGTH)][(MAPLENGHT)])[BGSPRITES_SIZE][BGSPRITES_SIZE];
    IVGA *vga;
    uint updateStartFrame = 0;     // on which frame the update started
    uint updateFrameDelay = 20; // how many frames has to pass for the next game update
public:
    virtual ~GAMEENGINE()
    {
        delete vga;
    };
    // Returns true if update is allowed, false if not
    virtual bool updateAllowed() = 0;
    virtual void GameLoop() = 0;
    virtual void Initialise_Buffer_BG()
    {
        unsigned char(*selected_array)[32];
        int arrayLine = 0;
        for (bg_generated_line = 0; bg_generated_line < BUFFER_LINE_SIZE; bg_generated_line++)
        {
            arrayLine = bg_generated_line_buffer / 32;
            for (int j = 0; j < MAPLENGHT; j++)
            {
                selected_array = *backgroundSpritesMap[arrayLine][j];
                memcpy(IVGA::genBuffer[bg_generated_line_buffer] + j * 32, selected_array[bg_generated_line % 32], 32);
            }
            bg_generated_line_buffer++;
        }
        bg_generated_line_buffer = 0;
    }

    virtual void fill_Bg_Sprites()
    {
        unsigned char(*selected_array)[32];
        int arrayLine = 0;
        for (; bg_generated_line < NUM_LINE_SCREEN; bg_generated_line++)
        {
            // printf("vga done line: %d, bg_gen_line: %d\n", IVGA::doneLine, bg_generated_line_buffer);
            if (IVGA::doneLine == bg_generated_line_buffer)
            {
                //gpio_put(TESTPIN, 0);
                return;
            } // return to not overtake the display
            arrayLine = bg_generated_line / 32;
            for (int j = 0; j < MAPLENGHT; j++)
            {
                selected_array = *backgroundSpritesMap[arrayLine][j];
                memcpy(IVGA::genBuffer[bg_generated_line_buffer] + j * 32, selected_array[bg_generated_line % 32], 32);
            }
            bg_generated_line_buffer = (bg_generated_line_buffer + 1) % BUFFER_LINE_SIZE;
        }
        bg_generated_line = 0;
    }
};

#endif