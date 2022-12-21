#include <iostream>
#include "Timer.hpp"
#include <thread>
#include <unistd.h>
#include "Clock.hpp"

int main()
{
    Timer timer;
    timer.Start();
    long now = Clock::Timestamp();
    timer.AddEvent(now+100,100);
    timer.AddEvent(now+10,10);
    timer.AddEvent(now+20,20);
    timer.AddEvent(now+30,30);
    timer.AddEvent(now+40,40);
    timer.PrintEvent();
    while (1)
    {
        sleep(1);
    }
    timer.Stop();
    return 0;
}