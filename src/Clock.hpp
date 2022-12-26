#pragma once

#include <sys/time.h>
#include <time.h>
#include <iostream>
#include "string_util.h"
class Clock
{
public:
static long Timestamp() {
    struct timeval tvt;
    gettimeofday(&tvt, 0);
    return static_cast<long>(tvt.tv_sec);
}

static long TimestampToday() {
    time_t t = time(NULL);
    struct tm * tm= localtime(&t);
    tm->tm_hour = 0;
    tm->tm_min = 0;
    tm->tm_sec = 0;
    return  mktime(tm);
}

static void Time()
{
    time_t now = time(NULL);
    struct tm* ptm = localtime(&now);
    std::cout  << ptm->tm_year << " " << ptm->tm_mon << " " << ptm->tm_mday << " " << ptm->tm_wday << std::endl;
    std::cout  << ptm->tm_hour << " " << ptm->tm_min << " " << ptm->tm_sec << std::endl;

    long timestamp = Timestamp();
    long timestampToday = TimestampToday();
    std::string formatDate =  Clock::GetFormatTime();
    std::cout << "timestamp:" << timestamp << " timestampToday:" << timestampToday << " format:" << formatDate << std::endl;

    int year,month,day,hour,min,sec;
    DateTimeByString(formatDate,year,month,day,hour,min,sec);
    std::cout << "year:" << year << " month:" << month << " day:" << day << std::endl;
    std::cout << "hour:" << hour << " min:" << min << " sec:" << sec << std::endl;

    time_t rawtime;
    struct tm * timeinfo;
    time ( &rawtime );
    timeinfo = localtime ( &rawtime );
    timeinfo->tm_year = year - 1900;
    timeinfo->tm_mon = month - 1;
    timeinfo->tm_mday = day;
    mktime ( timeinfo );

    printf ("That day is a %i.\n", timeinfo->tm_wday);
}

static double DiffTime(const std::string& date)
{
    int year;int month;int day;int hour;int minute;int second;
    DateTimeByString(date,year,month,day,hour,minute,second);
    time_t now;
    struct tm newyear;
    double seconds;

    time(&now);  /* get current time; same as: now = time(NULL)  */
    newyear = *localtime(&now);

    newyear.tm_hour = 0; 
    newyear.tm_min = 0; 
    newyear.tm_sec = 0;
    newyear.tm_year = year; 
    newyear.tm_mon = month;  
    newyear.tm_mday = day;

    seconds = difftime(now,mktime(&newyear));
    return seconds;
}

static std::string GetFormatTime()
{
	struct tm stime;
    time_t now = time(0);
    localtime_r(&now, &stime);
    char buffer[256] = {0};
	strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &stime);
    std::string date(buffer);
    return date;
}

static long TimeByString(const std::string& date)
{
    //date +%Y
    std::vector<std::string> dateTime = abby::StringUtil::Split(date,' ');
    if(dateTime.size()!=2) return 0;
    std::cout << "date:" << dateTime[0] << " time:" << dateTime[1] << std::endl;
    std::vector<std::string> times = abby::StringUtil::Split(dateTime[1],':');
    if(times.size()!=3) return 0;
    int hour = atoi(times[0].c_str());
    int minute = atoi(times[1].c_str());
    int second = atoi(times[2].c_str());
    return hour * 3600 + minute * 60 + second;
}

static void DateTimeByString(const std::string& date,
        int& year,int& month,int& day,int& hour,int& minute,int& second)
{
    //date +%Y
    std::vector<std::string> dateTime = abby::StringUtil::Split(date,' ');
    if(dateTime.size()!=2) return;
    std::cout << "date:" << dateTime[0] << " time:" << dateTime[1] << std::endl;
    std::vector<std::string> dates = abby::StringUtil::Split(dateTime[0],'-');
    if(dates.size()!=3) return;
    year = atoi(dates[0].c_str());
    month = atoi(dates[1].c_str());
    day = atoi(dates[2].c_str());
    std::cout << "year:" << year << " month:" << month << " day:" << day << std::endl;
    std::vector<std::string> times = abby::StringUtil::Split(dateTime[1],':');
    if(times.size()!=3) return;
    hour = atoi(times[0].c_str());
    minute = atoi(times[1].c_str());
    second = atoi(times[2].c_str());
    std::cout << "hour:" << hour << " min:" << minute << " sec:" << second << std::endl;
}

static long TimeToday()
{
    //date +%Y
    time_t t = time(NULL);
    struct tm * tm= localtime(&t);
    return tm->tm_hour * 3600 + tm->tm_min * 60 + tm->tm_sec;
}

static int Year(const std::string& date)
{
    //date +%Y
    std::vector<std::string> dateTime = abby::StringUtil::Split(date,' ');
    if(dateTime.size()!=2) return 0;
    std::cout << "date:" << dateTime[0] << " time:" << dateTime[1] << std::endl;
    std::vector<std::string> dates = abby::StringUtil::Split(dateTime[0],'-');
    if(dates.size()!=3) return 0;
    int year = atoi(dates[0].c_str());
    return year;
}

static int Year()
{
    //date +%Y
    time_t now = time(NULL);
    struct tm* ptm = localtime(&now);
    return ptm->tm_year;
}

static int Month()
{
    //date +%m
    time_t now = time(NULL);
    struct tm* ptm = localtime(&now);
    return ptm->tm_mon;
}

static int Day()
{
    //date +%d
    time_t now = time(NULL);
    struct tm* ptm = localtime(&now);
    return ptm->tm_mday;
}

static int Week(){
    //date +%w
    time_t now = time(NULL);
    struct tm* ptm = localtime(&now);
    return ptm->tm_wday;
}
};