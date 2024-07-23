#include "./vgaSaveNthFrame.h"

void vgaSaveNthFrame::sendNextLine()
{
    // std::cout << "line: " << (int)doneLine << std::endl;
    if (this->framecounter == this->frameToSave)
    {
        for (int i = 0; i < NUM_PIXELS_INLINE; i++)
        {
            outputFile << (int)genBuffer[doneLine][i] << " ";
        }
        outputFile << std::endl;
    }
    if (this->framecounter == (this->frameToSave + 1))
    {
        outputFile.close();
        std::cout << "done\n";
        exit(0);
    }
    if (IVGA::currentLineSend == 489)
    {
        this->framecounter++;
    }

    doneLine = (doneLine + 1) % BUFFER_LINE_SIZE;
}
