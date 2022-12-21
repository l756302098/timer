#pragma once

#include <map>
#include <atomic>
#include <memory>
#include <thread>
#include <mutex>
#include <iostream>
class Timer
{
private:
    /* data */
    std::map<long,int> events;
    std::mutex mtx;
    std::atomic<bool> running;
    std::unique_ptr<std::thread> timeThread;
private:
    void Tick();
public:
    Timer(/* args */);
    ~Timer();
    void PrintEvent();
    void AddEvent(long timestamp,int event);
    void DelEvent(long timestamp);
    void DelAll();
    void Start();
    void Stop();
};