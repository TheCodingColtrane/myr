#include "../include/investiments.h"
#include "../include/file.h"
#include "../include/date.h"
#include <iostream>
#include <fstream>
#include <algorithm>


time_t increment_month(time_t current_date)
{
    struct tm date_tm = *localtime(&current_date);
    date_tm.tm_mon += 1;
    date_tm.tm_mday = 1;
    return mktime(&date_tm);
}


float Investiment::profit(investiments investiments, std::vector<holidays> holidays)
{
    tm start_date = getnextbusinessday(investiments.starting_date), end_date = getnextbusinessday(investiments.ending_date);
    time_t starting_date = mktime(&start_date);
    int business_days = 0;
    investiments.rate /= 100;
    float monthly_yield = investiments.rate / 12, earnings = 0, daily_yield = 0;
    holidays = filterholidays(starting_date, holidays);
    for (time_t current_date = starting_date; current_date <= investiments.ending_date; current_date = increment_month(current_date))
    {
        struct tm date = *localtime(&current_date);
        business_days = getbusinessdays(date, holidays);
        if (business_days)
        {
            daily_yield = monthly_yield / business_days;
            earnings += investiments.value * (daily_yield * business_days);
        }

    }

    return investiments.value + earnings;
}
float Investiment::roi()
{
    return 0.0f;
}