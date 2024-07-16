#include "./vgaSaveFirstFrame.h"

void vgaSaveFirstFrame::sendNextLine()
{
    // std::cout << "line: " << (int)doneLine << std::endl;
    if (frameCounter == 1)
    {
        for (int i = 0; i < NUM_PIXELS_INLINE; i++)
        {
            outputFile << (int)genBuffer[doneLine][i] << " ";
        }
        outputFile << std::endl;
    }
    if (frameCounter > 1)
    {
        std::cout << "done\n";
    }
    if (IVGA::currentLineSend == 489)
    {
        frameCounter++;
    }

    doneLine = (doneLine + 1) % BUFFER_LINE_SIZE;
}
