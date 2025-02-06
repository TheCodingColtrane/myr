#include "../../include/date.h"
#include "../../include/file_parser.h"
#include "../../include/sort.h"
#include "../../include/http.h"
#include "../../include/json_parser.h"
#include <time.h>
#include <iostream>


struct tm getnextbusinessday(time_t &date)
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


time_t incrementdate(time_t current_date)
{
    struct tm date_tm = *localtime(&current_date);
    date_tm.tm_mday += 1;
    return mktime(&date_tm);
}

int getbusinessdays(tm date, vector<Investiment::holidays> saved_holidays)
{
    int month_days = getmonthdays(date), business_days = 0, i = 0, holidays_count = saved_holidays.size();
    time_t month_start = mktime(&date);
    struct tm final_date = date;
    final_date.tm_mday = month_days;
    time_t month_end = mktime(&final_date);
    for (time_t current_date = month_start; current_date <= month_end; current_date = incrementdate(current_date))
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


std::vector<Investiment::holidays> filterholidays(time_t& start_date, std::vector<Investiment::holidays> &saved_holidays)
{
    tm date = getnextbusinessday(start_date);
    time_t current_date = mktime(&date);
    int relevant_holidays_count = 0, holidays_count = saved_holidays.size();
    for (int i = 0; i < holidays_count; i++)
    {
        if (current_date > saved_holidays[i].date)
        {
            relevant_holidays_count = i;
            break;
        }

    }

    Investiment::holidays *relevant_holidays = new Investiment::holidays[relevant_holidays_count];
    for (int i = 0; i < relevant_holidays_count; i++)
    {
        relevant_holidays[i].date = saved_holidays[i].date;
    }
    holidays_count = relevant_holidays_count;
    holidaysheapsort(relevant_holidays, holidays_count, compareholidaysdate);
    saved_holidays.clear();
    for(int i = 0; i < holidays_count; i++){
        Investiment::holidays holiday = {};
        holiday.date = relevant_holidays[i].date;
        saved_holidays.push_back(holiday);
    }
    delete[] relevant_holidays;
    return saved_holidays;
}

std::string getholidays()
{
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

void convertdatetofileformat(tm& provided_date, string& data)
{
    int fpos = 0; 
    if(data[0] == ' ') fpos = 1;
    else fpos = 0;
    provided_date.tm_year = std::stoi(data.substr(fpos, fpos + 4)) - 1900;
    provided_date.tm_mon = std::stoi(data.substr(fpos + 5, fpos + 7)) - 1;
    provided_date.tm_mday = std::stoi(data.substr(fpos + 8));
}