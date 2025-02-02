#include "../include/investiments.h"
#include "../include/utils.h"
#include "../include/file.h"
#include <iostream>
#include <fstream>
#include <algorithm>

void  read_investiments(investiments** investiments)
{
  
  std::string file = "investimentos.csv", rows;
  read_csv(file, rows);
  std::string::difference_type n = std::count(rows.begin(), rows.end(), ';');
  *investiments = Parse_Investiments(rows, int(n));
}


time_t StrDate(char* date){
   struct tm datetime = {};
    char* result = strptime(date, "%d/%m/%Y", &datetime);
    if (!result) {
        std::cerr << "Error parsing date: " << date << "\n";
        return -1;
    }
    time_t parsedTime = mktime(&datetime);
    if (parsedTime == -1) {
        std::cerr << "Error converting to time_t: " << date << "\n";
    }
    return parsedTime;

}   

