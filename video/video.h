#ifndef video_h
#define video_h

#include "../Global.h"

class VIDEO
{
private:
    int8_t screen_pixels[320][240]{0};
public:
    VIDEO(/* args */);
    ~VIDEO();
    void addSprite(int8_t** sprite, int xPos, int yPos);


};


#endif