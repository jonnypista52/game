#ifndef vgasavefirstFrame_h
#define vgasavefirstFrame_h

#include <fstream>
#include <iostream>
#include "../../../vga/Ivga.h"

class vgaSaveFirstFrame : public IVGA
{
private:
    std::ofstream outputFile;
    int frameCounter = 0;
public:
    vgaSaveFirstFrame(/* args */){
        outputFile.open("saveFrame.txt");
        if(outputFile.fail()){
            std::cout<<"failed to open file\n";
        }
    }

    ~vgaSaveFirstFrame(){
        outputFile.close();
    }

    // sends the next line
    // saves the 1st generated frame into a file
    void sendNextLine() override;
    void sendBlank() {}

    //! TEST
    void fill() {}
    void fillDifferent() {}
};

#endif