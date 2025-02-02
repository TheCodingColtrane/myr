#include "../../include/investiments.h"
#include "../../include/utils.h"
#include <iostream>
investiments *Parse_Investiments(std::string& rows, int investiments_count)
{
    investiments *my_investiments = new investiments[investiments_count];
    std::string raw_rows = rows;
    int row_chars = raw_rows.size();
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
                    my_investiments[row_number].data_inicio = StrDate(current_row.substr(1, current_row.length()).data());
                    current_row = "";
                }

                column++;
            }
        }
        else
        {
            my_investiments[row_number].data_fim = StrDate(current_row.substr(1, current_row.length()).data());
            row_number++;
            current_row = "";
            column = 0;
        }
    }
    my_investiments[0].investiments_count = investiments_count;
    return my_investiments;
}

int Get_Row_Count(std::string *ptr_investiments)
{
    std::string investiments = *ptr_investiments;
    int investiments_chars = investiments.size();
    int row_count;
    for (int i = 0; i < investiments_chars; i++)
        if (investiments[i] == ';')
            row_count++;
    return row_count;
}

void To_File(std::string *ptr_investiments)
{
    std::string investiments = *ptr_investiments;
    int investiments_chars = investiments.size();
    int row_count;
    for (int i = 0; i < investiments_chars; i++)
        if (investiments[i] == ';')
            investiments[i] = '\n';
    ptr_investiments = &investiments;
}

std::string To_DateTime(time_t time, const char *format)
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