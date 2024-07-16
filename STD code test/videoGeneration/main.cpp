#include <iostream>
#include <chrono>
#include <thread>
#include "../../GameLogic/videoGen/videoGen.h"
#include "./mockupVGAout/vgaSaveFirstFrame.h"
#include <atomic>

using namespace std;
using namespace std::this_thread; // sleep_for, sleep_until
using namespace std::chrono;      // nanoseconds, system_clock, seconds

//***! TEST
void gpio_put(int pin, bool val) {}

std::atomic<bool> running(true);
IVGA *vgamockup;
void repeatFunction()
{
    while (running)
    {
        // The function to be executed repeatedly

        if (IVGA::currentLineSend >= 10 && IVGA::currentLineSend < 490)
        {
            vgamockup->sendNextLine();
        }
        else
        {
            vgamockup->sendBlank();
        }
        IVGA::currentLineSend = (IVGA::currentLineSend + 1) % 524;
        // Sleep for a set amount of time (e.g., 1 second)
        //sleep_until(system_clock::now() + milliseconds(10));
    }
}

int main()
{
    vgamockup = new vgaSaveFirstFrame();
    VideoGen vGen(vgamockup);
    vGen.random_Bg_Sprites_init(0);
    cout << "generated background \n";

    std::thread repeatingThread(repeatFunction);
    while (true)
    {
        vGen.fill_Bg_Sprites();
        sleep_until(system_clock::now() + milliseconds(50));
    }

    sleep_for(nanoseconds(10));

    return 0;
}