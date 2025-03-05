#ifndef vgamockup_h
#define vgamockup_h


#include <iostream>
#include "../../../vga/Ivga.h"

class vgaMockup : public IVGA
{
private:
    /* data */
public:
    vgaMockup(){}
    
    // sends the next line
    void sendNextLine() override;
    void sendBlank() override;

    //! TEST
    void fill() override;
    void fillDifferent() override;
};

#endif