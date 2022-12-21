#pragma once

#include <sys/time.h>
#include <time.h>
#include <iostream>

class Clock
{
public:
static long Timestamp() {
    struct timeval tvt;
    gettimeofday(&tvt, 0);
    return static_cast<long>(tvt.tv_sec);
}

static void Time()
{
    time_t now = time(NULL);
    struct tm* ptm = localtime(&now);
    std::cout  << ptm->tm_year << " " << ptm->tm_mon << " " << ptm->tm_mday << " " << ptm->tm_wday << std::endl;
    std::cout  << ptm->tm_hour << " " << ptm->tm_min << " " << ptm->tm_sec << std::endl;
}

static uint32_t Year()
{
    //date +%Y
    return 0;
}

static uint32_t Month()
{
    //date +%m
    return 0;
}

static uint16_t Day()
{
    //date +%d
    return 0;
}

static uint16_t Week(){
    //date +%w
    return 0;
}

};