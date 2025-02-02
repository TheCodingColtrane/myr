#include "../../include/date.h"
#include "../../include/file_parser.h"
#include "../../include/sort.h"
#include "../../include/http.h"
#include "../../include/json_parser.h"
#include <time.h>
#include <iostream>

time_t strdate(char *date, std::string &format)
{
    struct tm datetime = {};
    char *result = strptime(date, format.data(), &datetime);
    if (!result)
    {
        std::cerr << "Error parsing date: " << date << "\n";
        return -1;
    }
    time_t parsedTime = mktime(&datetime);
    if (parsedTime == -1)
    {
        std::cerr << "Error converting to time_t: " << date << "\n";
    }
    return parsedTime;
}

struct tm next_business_day(time_t &date)
{
    tm start_date = *localtime(&date);
    if (start_date.tm_wday == 6)
        start_date.tm_wday += 2;
    else if (start_date.tm_wday == 0)
        start_date.tm_wday += 1;
    else
    {
        if (start_date.tm_wday == 5)
            start_date.tm_wday += 3;
        else
            start_date.tm_wday += 1;
    }

    return start_date;
}

int getmonthdays(tm date)
{
    if (date.tm_mon == 1)
    {
        int year = date.tm_year + 1900;
        if (year % 4 == 0)
            return 29;
        else
            return 28;
    }
    if (date.tm_mon == 3 || date.tm_mon == 5 || date.tm_mon == 8 || date.tm_mon == 10)
        return 30;
    else
        return 31;
}

std::string todatetimestr(time_t time, const char *format)
{
    char buffer[100];
    struct tm *timeinfo = localtime(&time);
    if (timeinfo == nullptr)
    {
        return "Invalid time";
    }
    strftime(buffer, sizeof(buffer), format, timeinfo);
    return std::string(buffer);
}

time_t increment_date(time_t current_date)
{
    struct tm date_tm = *localtime(&current_date);
    date_tm.tm_mday += 1;
    return mktime(&date_tm);
}

int businessdays(tm date, holidays *saved_holidays, int &holidays_count)
{
    int month_days = getmonthdays(date), business_days = 0, i = 0;
    time_t month_start = mktime(&date);
    struct tm final_date = date;
    final_date.tm_mday = month_days;
    time_t month_end = mktime(&final_date);
    for (time_t current_date = month_start; current_date <= month_end; current_date = increment_date(current_date))
    {
        struct tm date = *localtime(&current_date);
        if (date.tm_wday == 6 || date.tm_wday == 0)
            continue;
        if (holidays_count > 0)
        {
            if (current_date > saved_holidays[i].date)
            {
                i++;
                business_days++;
                continue;
            }
            else if (current_date < saved_holidays[i].date)
            {
                business_days++;
                continue;
            }
        }

        business_days++;
    }

    return business_days;
}

holidays filter_holidays(time_t start_date, holidays *saved_holidays, int &holidays_count)
{
    tm date = next_business_day(start_date);
    time_t current_date = mktime(&date);
    int relevant_holidays_count = 0;
    for (int i = 0; i < holidays_count; i++)
    {
        if (current_date > saved_holidays[i].date)
        {
            relevant_holidays_count = i;
            break;
        }
    }

    holidays *relevant_holidays = new holidays[relevant_holidays_count];
    for (int i = 0; i < relevant_holidays_count; i++)
    {
        relevant_holidays[i].date = saved_holidays[i].date;
    }
    holidays_count = relevant_holidays_count;
    saved_holidays = relevant_holidays;
    holidaysheapsort(saved_holidays, holidays_count, compareholidaysdate);
    return *saved_holidays;
}


std::string getholidays(){    
        time_t date = time(&date);
        struct tm datetime = *localtime(&date);
        int current_year = datetime.tm_year + 1900;
        int years = current_year - 1990;
        std::string json_holidaysm, holidays_file_content, json_holidays;
        for (int year = current_year; year >= 1990; year--)
        {
            std::string uri = "https://brasilapi.com.br/api/feriados/v1/" + std::to_string(year);
            json_holidays = get(uri);
            holidays_file_content += parse_json_holidays(json_holidays);
        }

        return holidays_file_content;
}