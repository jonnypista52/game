#ifndef vgamockup_h
#define vgamockup_h


#include <iostream>
#include "../../vga/Ivga.h"

class vgaMockup : public IVGA
{
private:
    /* data */
public:
    vgaMockup(){}
    // sends the next data line
    static void sendNextLine();
    // sends an blank black line
    static void sendBlank();

    //! TEST
    // implement as you wish
    void fill() override;
    // implement as you wish
    void fillDifferent() override;
};

#endif