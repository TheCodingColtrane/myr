#include <string>
#include "../include/file_parser.h"
time_t strdate(char* date, std::string &format);
struct tm next_business_day(time_t &date);
holidays filter_holidays(time_t start_date, holidays *saved_holidays, int &holidays_count);
int getmonthdays(tm date);
int businessdays(tm date, holidays *saved_holidays, int &holidays_count);
std::string todatetimestr(time_t time, const char *format);
std::string getholidays();