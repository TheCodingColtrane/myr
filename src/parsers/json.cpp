#include "../../include/json_parser.h"
#include "../../include/indexes.h"
#include <vector>
#include <iostream>
#include <string>
using namespace simdjson;
using namespace std;
void addindex(string &date, string &value, int &type, vector<Indexes::volatile_index>& indexes)
{
    Indexes::volatile_index index = {};
    index.date.tm_year = stoi(date.substr(6)) - 1900;
    index.date.tm_mon = stoi(date.substr(3, 2)) - 1;
    index.date.tm_mday = stoi(date.substr(0, 2));
    index.type = type;
    index.rate = stof(value);
    indexes.push_back(index);

}



string parse_json_holidays(string &json)
{
    ondemand::parser parser;
    padded_string padded_json(json);
    auto parsed_json = parser.iterate(padded_json);
    if (parsed_json.error() != simdjson::SUCCESS)
    {
        string errStr = simdjson::error_message(parsed_json.error()) ? string(simdjson::error_message(parsed_json.error())) : "";
        string what = "Failed to load json document: " + errStr;
    }

    string holidays_file_content, holiday_name, holiday_date;
    for (auto holiday : parsed_json)
    {
        // holiday_name = holiday["name"].get_string().value();
        holiday_date = holiday["date"].get_string().value();
        // holidays_file_content += holiday_name + "," + holiday_date + '\n';
        holidays_file_content += holiday_date + '\n';
    }
    return holidays_file_content;
}


void parse_json_indices(string &json, vector<Indexes::volatile_index> &indexes, int &type)
{
    ondemand::parser parser;
    padded_string padded_json(json);
    auto parsed_json = parser.iterate(padded_json);
    if (parsed_json.error() != simdjson::SUCCESS)
    {
        string errStr = simdjson::error_message(parsed_json.error()) ? string(simdjson::error_message(parsed_json.error())) : "";
        string what = "Failed to load json document: " + errStr;
    }

    string indice_value, indice_date;
    int i = 0;
    for (auto indice : parsed_json)
    {
        indice_date = indice["data"].get_string().value();
        indice_value = indice["valor"].get_string().value();
        addindex(indice_date, indice_value, type, indexes);    
    }
    // return indice_file_content;
}
