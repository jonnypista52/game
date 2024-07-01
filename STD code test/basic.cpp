#include <iostream>
#include <chrono>
#include <thread>

using namespace std;

#define BUFFER_LINE_SIZE 96

int main()
{
    int doneLine = 0;
    while (true)
    {
        doneLine = (doneLine + 1) % BUFFER_LINE_SIZE;
        cout << doneLine << " "<<endl;
        using namespace std::this_thread; // sleep_for, sleep_until
        using namespace std::chrono;      // nanoseconds, system_clock, seconds

        sleep_for(nanoseconds(10));
        sleep_until(system_clock::now() + milliseconds(50));
    }

    return 0;
}