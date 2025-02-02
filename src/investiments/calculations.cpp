#include "../../include/file_parser.h"
#include "../../include/date.h"

#include <time.h>

// float Yield(investiments &investment, time_t *holidays)
// {
//     return 70;
// }

tm get_date(time_t date)
{
    date = time(&date);
    struct tm datetime = *gmtime(&date);
    return datetime;
};

time_t increment_month(time_t current_date)
{
    struct tm date_tm = *localtime(&current_date);
    date_tm.tm_mon += 1;
    date_tm.tm_mday = 1;
    return mktime(&date_tm);
}


float yield(time_t &starting_date, time_t &ending_date, holidays *holidays, int holidays_count, float yield, float money)
{
    tm start_date = next_business_day(starting_date), end_date = next_business_day(ending_date);
    starting_date = mktime(&start_date);
    int business_days = 0;
    yield /= 100;
    float monthly_yield = yield / 12, earnings = 0, daily_yield = 0;
    *holidays = filter_holidays(starting_date, holidays, holidays_count);
    for (time_t current_date = starting_date; current_date <= ending_date; current_date = increment_month(current_date))
    {
        struct tm date = *localtime(&current_date);
        business_days = businessdays(date, holidays, holidays_count);
        if (business_days)
        {
            daily_yield = monthly_yield / business_days;
            earnings += money * (daily_yield * business_days);
        }

    }

    return money + earnings;

}
