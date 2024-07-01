#include "./videoGen.h"

VideoGen::VideoGen(VGA *vga)
{
    this->vga = vga;
}

VideoGen::~VideoGen()
{
    delete vga;
}

void VideoGen::random_Bg_Sprites_init(int nrOfSprites)
{
    for (int i = 0; i < MAPLENGHT; i++)
    {
        for (int j = 0; j < MAPHEIGTH; j++)
        {
            int random = rand() % (nrOfSprites + 1);
            // cout << random << " ";
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

void VideoGen::fill_Bg_Sprites(){
    int offset;
    unsigned char(*selected_array)[32];
    
    for (int i = 0; i < NUM_LINE_SCREEN; i++)
    {
        while(VGA::doneLine == bg_generated_line);//wait to not overtake the display
        for (int j = 0; j < MAPLENGHT; j++)
        {
            selected_array = *backgroundSpritesMap[i / 32][j];
            memcpy(VGA::genBuffer[bg_generated_line] + j * 32, selected_array[i % 32], 32);
        }
        bg_generated_line = (bg_generated_line+1)%BUFFER_LINE_SIZE;
    }
}
