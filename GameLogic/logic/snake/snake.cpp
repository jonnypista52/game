#include "./snake.h"

SNAKE::SNAKE(IVGA *vga)
{
    this->Coordinatestmp.x = 4;
    this->Coordinatestmp.y = 4;
    this->vga = vga;

    for (int i = 0; i < MAPHEIGTH; i++)
    {
        for (int j = 0; j < MAPLENGHT; j++)
        {
            this->backgroundSpritesMap[i][j] = &specialist_pixel_data;
        }
    }

    snakePositions.push_front(this->Coordinatestmp);
    this->backgroundSpritesMap[4][4] = &supporter_pixel_data;
}

SNAKE::~SNAKE()
{
}
// TODO just make the game
void SNAKE::GameLoop()
{
    //gpio_put(TESTPIN, 0);
    this->backgroundSpritesMap[this->Coordinatestmp.x][this->Coordinatestmp.y] = &blank_pixel_data;
    this->Coordinatestmp.y = (this->Coordinatestmp.y + 1) % (MAPLENGHT);
    this->backgroundSpritesMap[this->Coordinatestmp.x][this->Coordinatestmp.y] = &supporter_pixel_data;
    //gpio_put(TESTPIN, 1);
}

void SNAKE::fill_Bg_Sprites()
{
    unsigned char(*selected_array)[32];
    int arrayLine = 0;
    for (; bg_generated_line < NUM_LINE_SCREEN; bg_generated_line++)
    {
        arrayLine = bg_generated_line / 32;
        // printf("vga done line: %d, bg_gen_line: %d\n", IVGA::doneLine, bg_generated_line_buffer);
        if (IVGA::doneLine == bg_generated_line_buffer)
        {
            return;
        } // return to not overtake the display
        for (int j = 0; j < MAPLENGHT; j++)
        {
            selected_array = *backgroundSpritesMap[arrayLine][j];

            memcpy(IVGA::genBuffer[bg_generated_line_buffer] + j * 32, selected_array[bg_generated_line % 32], 32);
        }
        bg_generated_line_buffer = (bg_generated_line_buffer + 1) % BUFFER_LINE_SIZE;
    }
    bg_generated_line = 0;
}