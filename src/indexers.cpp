#include "../include/indexes.h"
#include "../include/json_parser.h"
#include "../include/http.h"
#include "../include/file.h"
using namespace std;

void removeselicduplicates(vector<Indexes::volatile_index> &selic_data)
{
    Indexes::volatile_index current_selic = {};
    int selic_count  = selic_data.size();
    current_selic = selic_data[0];
    vector<Indexes::volatile_index> filtered_selic_data;
    filtered_selic_data.push_back(current_selic);
    for(int i = 1; i < selic_count; i++){
        if(current_selic.rate != selic_data[i].rate){
            filtered_selic_data.push_back(selic_data[i]);
            current_selic = selic_data[i];    
        }
        
    }
    selic_data = filtered_selic_data;   
   
}



std::string Indexes::indextocsvfile(std::vector<Indexes::volatile_index> &index_data)
{
    string file_data = "";
    for (auto index : index_data)
    {
        
        int month = index.date.tm_mon + 1, day = index.date.tm_mday;
        string month_str = "", day_str = "";
        if(month < 10) month_str = "0" + to_string(month);
        else month_str = to_string(month);
        if(day < 10) day_str = "0" + to_string(day);
        else day_str = to_string(day);
        file_data += to_string((index.date.tm_year + 1900)) + "-" + month_str + "-" + day_str+ ", " + to_string(index.rate) + ", " + to_string(index.type) + "\n";
    }
    return file_data;
}


vector<Indexes::volatile_index> Indexes::createindexes(bool update)
{
    string selic = "https://api.bcb.gov.br/dados/serie/bcdata.sgs.1178/dados?formato=json";
    string ipca = "https://api.bcb.gov.br/dados/serie/bcdata.sgs.16122/dados?formato=json";
    string cdi = "https://api.bcb.gov.br/dados/serie/bcdata.sgs.4391/dados?formato=json";
    string json_selic = get(selic);
    string json_ipca = get(ipca);
    string json_cdi = get(cdi);
    vector<Indexes::volatile_index> indices = {};
    int type = 0;
    parse_json_indices(json_selic, indices, type);
    int *auxiliary = new int[3];
    auxiliary[0] = indices.size() - 1;
    vector<Indexes::volatile_index> ordered_indices = {};
    for (int i = auxiliary[0]; i > -1; i--)
    {
        ordered_indices.push_back(indices[i]);
    }

    removeselicduplicates(ordered_indices);
    indices.clear();
    type++;
    parse_json_indices(json_ipca, indices, type);
    auxiliary[1] = indices.size();
    for (int i = auxiliary[1]; i > -1; i--)
    {
        ordered_indices.push_back(indices[i]);
    }
    indices.clear();
    type++;
    parse_json_indices(json_cdi, indices, type);
    auxiliary[2] = indices.size();
    for (int i = auxiliary[2]; i > -1; i--)
    {
        ordered_indices.push_back(indices[i]);
    }

    return ordered_indices;
}