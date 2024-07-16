#include "./videoGen.h"

VideoGen::VideoGen(IVGA *vga)
{
    this->vga = vga;
}

VideoGen::~VideoGen()
{
}

void VideoGen::random_Bg_Sprites_init(int nrOfSprites)
{
    for (int i = 0; i < MAPHEIGTH; i++)
    {
        for (int j = 0; j < MAPLENGHT; j++)
        {
            int random = rand() % (nrOfSprites + 1);
            switch (random)
            {
            case 0:
                backgroundSpritesMap[i][j] = &caster_pixel_data;
                break;
            case 1:
                backgroundSpritesMap[i][j] = &medic_pixel_data;
                break;
            case 2:
                backgroundSpritesMap[i][j] = &guard_pixel_data;
                break;
            case 3:
                backgroundSpritesMap[i][j] = &medic_pixel_data;
                break;
            case 4:
                backgroundSpritesMap[i][j] = &sniper_pixel_data;
                break;
            case 5:
                backgroundSpritesMap[i][j] = &specialist_pixel_data;
                break;
            case 6:
                backgroundSpritesMap[i][j] = &supporter_pixel_data;
                break;
            case 7:
                backgroundSpritesMap[i][j] = &vanguard_pixel_data;
                break;
            default:
                backgroundSpritesMap[i][j] = &medic_pixel_data;
                break;
            }
        }
    }
}

void VideoGen::fill_Bg_Sprites()
{
    unsigned char(*selected_array)[32];
    int arrayLine = 0;
    for (int i = 0; i < BUFFER_LINE_SIZE; i++)
    {
        arrayLine = i / 32;
        //printf("vga done line: %d, bg_gen_line: %d\n", IVGA::doneLine, bg_generated_line);
        //while (IVGA::doneLine == bg_generated_line); // wait to not overtake the display
        for (int j = 0; j < (MAPLENGHT); j++)
        {
            selected_array = *backgroundSpritesMap[arrayLine][j];
            //gpio_put(TESTPIN, 0);
            memcpy(IVGA::genBuffer[bg_generated_line] + j * 32, selected_array[i % 32], 32);
            //gpio_put(TESTPIN, 1);
        }
        bg_generated_line = (bg_generated_line + 1) % BUFFER_LINE_SIZE;
    }
}
