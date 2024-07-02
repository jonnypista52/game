#include <iostream>
#include <chrono>
#include <thread>
#include "./vgamockup.cpp"

using namespace std;
using namespace std::this_thread; // sleep_for, sleep_until
using namespace std::chrono;      // nanoseconds, system_clock, seconds

int main()
{

    sleep_for(nanoseconds(10));
    sleep_until(system_clock::now() + milliseconds(50));

    return 0;
}