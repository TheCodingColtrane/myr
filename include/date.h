#include <string>
#include "../include/investiments.h"

struct tm getnextbusinessday(time_t &date);
int getmonthdays(tm date);
int getbusinessdays(tm date, std::vector<Investiment::holidays> saved_holidays);
std::string getholidays();
void convertdatetofileformat(tm& provided_date, std::string& data);
std::vector<Investiment::holidays> filterholidays(time_t& start_date, std::vector<Investiment::holidays> &saved_holidays);
