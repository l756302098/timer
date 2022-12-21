#include "Timer.hpp"
#include "Clock.hpp"
#include <unistd.h>
#include <functional>

Timer::Timer(/* args */){

}
Timer::~Timer(){}
void Timer::PrintEvent()
{
    for (std::map<long,int>::iterator it=events.begin(); it!=events.end(); ++it)
    {
        std::cout << "key:" << it->first << " value:" << it->second << std::endl;
    }
    
}
void Timer::AddEvent(long timestamp,int event){
    std::lock_guard<std::mutex> lck (mtx);
    events.insert(std::pair<long,int>(timestamp,event));
}
void Timer::DelEvent(long timestamp){
    std::lock_guard<std::mutex> lck (mtx);
    auto it = events.find(timestamp);
    if(it!=events.end()){
        events.erase (it);
    }
}
void Timer::DelAll(){
    std::lock_guard<std::mutex> lck (mtx);
    events.clear();
}
void Timer::Tick(){
    while (running)
    {
        //std::cout << "running..." << std::endl;
        if(!events.empty())
        {
            long now = Clock::Timestamp();
            //std::cout << "now:" << now << std::endl;
            if(now)
            {
                std::lock_guard<std::mutex> lck (mtx);
                for (std::map<long,int>::iterator it=events.begin(); it!=events.end(); ++it)
                {
                    //std::cout << it->first << ": " << it->second << '\n';
                    if(it->first > now)
                    {
                        //std::cout << "break" << std::endl;
                        break;
                    }
                    else
                    {
                        //std::cout << "erase " << it->first << std::endl;
                        events.erase (it);
                        break;
                    }
                }
            }
        }
        //std::cout << "sleep..." << std::endl;
        sleep(1);
    }
}

void Timer::Start()
{
    running = true;
    timeThread.reset(new std::thread(std::bind(&Timer::Tick, this)));
}
void Timer::Stop(){
    running = false;
}