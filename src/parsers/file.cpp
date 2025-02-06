#include "../../include/file_parser.h"
#include "../../include/date.h"
#include "../../include/indexes.h"
#include "../../include/investiments.h"
#include <algorithm>
#include <iostream>
#include <vector>

std::vector<Indexes::volatile_index> parseindexers(std::string &rows)
{
    std::vector<Indexes::volatile_index> indexes = {};
    Indexes::volatile_index index = {};
    int char_count = rows.size(), column = 0;
    std::string data = "";
    for (int i = 0; i < char_count; i++)
    {
        if (rows[i] != '\n')
        {
            if (rows[i] != ',')
            {
                data += rows[i];
                continue;
            }
            else
            {
                if (!column)
                {
                    index.date.tm_year = std::stoi(data.substr(0, 4)) - 1900;
                    index.date.tm_mon = std::stoi(data.substr(5, 7)) - 1;
                    index.date.tm_mday = std::stoi(data.substr(8));
                    column++;
                    data = "";
                }
                else if (column == 1)
                {
                    index.rate = std::stof(data);
                    column++;
                    data = "";
                }
            }
        }
        else
        {
            index.type = std::stoi(data);
            data = "";
            column = 0;
            indexes.push_back(index);

        }
    }

   return indexes;

}

std::vector<Investiment::investiments> parseinvestiments(std::string &rows)
{
    std::vector<Investiment::investiments> investiments = {};
    struct Investiment::investiments investiment = {};
    int char_count = rows.length();
    int column = 0;
    int row_number = 0;
    std::string current_row;
    tm data = {};

    for (int i = 0; i < char_count; i++)
    {
        if (rows[i] != '\n')
        {
            if (rows[i] != ',')
            {
                current_row += rows[i];
                continue;
            }
            else
            {
                if (!column)
                {
                    investiment.asset_name = current_row;
                    current_row = "";
                }
                else if (column == 1)
                {
                    investiment.rate = stod(current_row);
                    current_row = "";
                }
                else if (column == 2)
                {
                    investiment.value = stod(current_row);
                    current_row = "";
                }
                else if (column == 3)
                {   
                    convertdatetofileformat(data, current_row);
                    investiment.starting_date = mktime(&data);
                    current_row = "";
                }

                column++;
            }
        }
        else
        {
            convertdatetofileformat(data, current_row);
            investiment.ending_date = mktime(&data);
            current_row = "";
            investiments.push_back(investiment);
            column = 0;
        }
    }
    return investiments;
    
}


std::vector<Investiment::holidays> parseholidays(std::string &rows)
{
    std::vector<Investiment::holidays> relevant_holidays;
    struct tm date = {};
    Investiment::holidays holidays = {};
    std::string raw_rows = rows, temp_date = "";
    int row_chars = raw_rows.length();
    int aux = 0;
    for (int i = 0; i < row_chars; i++)
    {
        if (raw_rows[i] == '\n'){
        date.tm_year =  std::stoi(temp_date.substr(0, 4)) - 1900;
        date.tm_mon = std::stoi(temp_date.substr(5, 2)) - 1;
        date.tm_mday = std::stoi(temp_date.substr(8, 2));
        holidays.date = mktime(&date);
        relevant_holidays.push_back(holidays);
        holidays = {};
        i += 11;
        temp_date = "";
        continue;
        }

        else temp_date += raw_rows[i]; 
    
    }
    return relevant_holidays;
}

