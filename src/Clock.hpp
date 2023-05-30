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


// Function to convert unix time to
// Human readable format
static std::string unixTimeToHumanReadable(long int seconds)
{

    // Save the time in Human
    // readable format
    std::string ans = "";

    // Number of days in month
    // in normal year
    int daysOfMonth[] = { 31, 28, 31, 30, 31, 30,
                          31, 31, 30, 31, 30, 31 };

    int currYear, daysTillNow, extraTime, extraDays,
        index, date, month, hours, minutes, secondss,
        flag = 0;

    // Calculate total days unix time T
    daysTillNow = seconds / (24 * 60 * 60);
    extraTime = seconds % (24 * 60 * 60);
    currYear = 1970;

    // Calculating current year
    while (true) {
        if (currYear % 400 == 0
            || (currYear % 4 == 0 && currYear % 100 != 0)) {
            if (daysTillNow < 366) {
                break;
            }
            daysTillNow -= 366;
        }
        else {
            if (daysTillNow < 365) {
                break;
            }
            daysTillNow -= 365;
        }
        currYear += 1;
    }
    // Updating extradays because it
    // will give days till previous day
    // and we have include current day
    extraDays = daysTillNow + 1;

    if (currYear % 400 == 0
        || (currYear % 4 == 0 && currYear % 100 != 0))
        flag = 1;

    // Calculating MONTH and DATE
    month = 0, index = 0;
    if (flag == 1) {
        while (true) {

            if (index == 1) {
                if (extraDays - 29 < 0)
                    break;
                month += 1;
                extraDays -= 29;
            }
            else {
                if (extraDays - daysOfMonth[index] < 0) {
                    break;
                }
                month += 1;
                extraDays -= daysOfMonth[index];
            }
            index += 1;
        }
    }
    else {
        while (true) {

            if (extraDays - daysOfMonth[index] < 0) {
                break;
            }
            month += 1;
            extraDays -= daysOfMonth[index];
            index += 1;
        }
    }

    // Current Month
    if (extraDays > 0) {
        month += 1;
        date = extraDays;
    }
    else {
        if (month == 2 && flag == 1)
            date = 29;
        else {
            date = daysOfMonth[month - 1];
        }
    }

    // Calculating HH:MM:YYYY
    hours = extraTime / 3600;
    minutes = (extraTime % 3600) / 60;
    secondss = (extraTime % 3600) % 60;

    char *buff = new char[128];
    sprintf(buff,"%4i-%02i-%02i %02i:%02i:%02i",currYear,month,date,hours,minutes,secondss);
    ans = std::string(buff);
    // Return the time
    return ans;
}

static long toTimestamp(const std::string& date){
    std::vector<std::string> splits = abby::StringUtil::Split(date,' ');
    for (size_t i = 0; i < splits.size(); i++)
    {
        std::cout << "index:" << i << " " << splits[i] << std::endl;
    }
    std::string d = splits[0];
    std::string s = splits[1];
    
    std::vector<std::string> dSplits = abby::StringUtil::Split(d,'-');
    // for (size_t i = 0; i < dSplits.size(); i++)
    // {
    //     std::cout << "year index:" << i << " " << dSplits[i] << std::endl;
    // }

    std::vector<std::string> sSplits = abby::StringUtil::Split(s,':');
    // for (size_t i = 0; i < sSplits.size(); i++)
    // {
    //     std::cout << "time index:" << i << " " << sSplits[i] << std::endl;
    // }
    int years = stoi(dSplits[0]);
    int tempy = 1970;
    int otherDay = 0;
    while (tempy < years)
    {
        if (tempy % 400 == 0
        || (tempy % 4 == 0 && tempy % 100 != 0)){
            otherDay += 1;
        }
        tempy += 1;
    }

    int year = years - 1970;
    int month = stoi(dSplits[1]);
    int days = stoi(dSplits[2]) - 1;

    if(month>2)
    {
        if (years % 400 == 0
        || (years % 4 == 0 && years % 100 != 0)){
            otherDay += 1;
        }
    }
    std::cout << "year:" << year << " month:" << month << " days:" << days << std::endl;
    
    int hours = stoi(sSplits[0]);
    int minent = stoi(sSplits[1]);
    int seconds = stoi(sSplits[2]);
    std::cout << "hours:" << hours << " minent:" << minent << " seconds:" << seconds << std::endl;


    int daysOfMonth[] = { 31, 28, 31, 30, 31, 30,
                          31, 31, 30, 31, 30, 31 };
    long dayTime = 3600 * 24;
    long day = year * 365;
    std::cout << "day:" << day << std::endl;
    for (size_t i = 0; i < month - 1; i++)
    {
        day += daysOfMonth[i];
    }
    std::cout << "day:" << day << std::endl;
    day += days;
    std::cout << "day:" << day << std::endl;
    day += otherDay;
    long timestamp = day * dayTime  + hours * 3600 + minent * 60 + seconds;

    return timestamp;
} 

};
