#ifndef UTILS_H
#define UTILS_H
#include "investiments.h"

investiments* Parse_Investiments(std::string& rows,int investiments_count);
int Get_Row_Count(std::string* ptr_investiments);
void To_File(std::string* ptr_investiments);
time_t StrDate(char* date);
std::string To_DateTime(time_t time, const char* format);
#endif