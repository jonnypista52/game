#ifndef vgasaveNthFrame_h
#define vgasaveNthFrame_h

#include <fstream>
#include <iostream>
#include "../../../vga/Ivga.h"

class vgaSaveNthFrame : public IVGA
{
private:
    std::ofstream outputFile;
    uint frameToSave;
public:
    vgaSaveNthFrame(uint frameToSave)
    {
        this->frameToSave = frameToSave;
        printf("vgaSaveNthFrame constructor\n");
        outputFile.open("saveFrame.txt");
        if (outputFile.fail())
        {
            std::cout << "failed to open file\n";
        }
    }

    ~vgaSaveNthFrame()
    {
        outputFile.close();
    }

    // sends the next line
    // saves the 1st generated frame into a file
    void sendNextLine() override;
    void sendBlank() {}
    void enablePIO() {};

    //! TEST
    void fill() {}
    void fillDifferent() {}
};

#endif