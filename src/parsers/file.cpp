#include "../../include/file_parser.h"
#include "../../include/date.h"
#include "../../include/indexes.h"
#include <algorithm>
#include <iostream>
#include <vector>
std::string local_date_format = "%d/%m/%Y";
std::string base_date_format = "%Y-%m-%d";

investiments *parse_investiments(std::string &rows)
{
    std::string::difference_type investiments_count = std::count(rows.begin(), rows.end(), ';');
    investiments *my_investiments = new investiments[investiments_count];
    std::string raw_rows = rows;
    int row_chars = raw_rows.length();
    int column = 0;
    int row_number = 0;
    std::string current_row;

    for (int i = 0; i < row_chars; i++)
    {
        if (raw_rows[i] != ';')
        {
            if (raw_rows[i] != ',')
            {
                current_row += raw_rows[i];
                continue;
            }
            else
            {
                if (!column)
                {
                    my_investiments[row_number].nome = current_row;
                    current_row = "";
                }
                else if (column == 1)
                {
                    my_investiments[row_number].percentual = stod(current_row);
                    current_row = "";
                }
                else if (column == 2)
                {
                    my_investiments[row_number].valor_investido = stod(current_row);
                    current_row = "";
                }
                else if (column == 3)
                {
                    my_investiments[row_number].data_inicio = strdate(current_row.substr(1, current_row.length()).data(), local_date_format);
                    current_row = "";
                }

                column++;
            }
        }
        else
        {
            my_investiments[row_number].data_fim = strdate(current_row.substr(1, current_row.length()).data(), local_date_format);
            row_number++;
            current_row = "";
            column = 0;
        }
    }
    return my_investiments;
}

holidays *parse_holidays(std::string &rows)
{
    std::string::difference_type holidays_count = std::count(rows.begin(), rows.end(), '\n');
    holidays *relevant_holidays = new holidays[holidays_count];
    std::string raw_rows = rows;
    int row_chars = raw_rows.length();
    int aux = 0;
    int row_number = 0;
    for (int i = 0; i < row_chars; i++)
    {
        if (raw_rows[i] == '\n')
            continue;
        relevant_holidays[row_number].date = strdate(raw_rows.substr(i, i + 10).data(), base_date_format);
        i += 10;
        row_number++;
    }
    return relevant_holidays;
}

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
