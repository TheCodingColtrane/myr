#include "../include/cli.h"
#include "../include/indexes.h"
#include "../include/bufferedfile.h"
#include "../include/file.h"
#include "../include/json_parser.h"
#include "../include/file_parser.h"
#include <iostream>
#include "../include/calculations.h"
#include "../include/sort.h"
int main()
{
    // investiments *rows = nullptr;
    // read_investiments(&rows);
    // int row_count = rows[0].investiments_count;
    // std::string holidays_file_content;
    // investimentheapsort(rows, row_count, compareinvestmentdate);
    // std::cout << "Seus investimentos:" << std::endl;
    // for (int i = 0; i < row_count; i++)
    // {
    //     std::cout << rows[i].nome + " | " + std::to_string(rows[i].percentual) + " | " + std::to_string(rows[i].valor_investido) + " | " + To_DateTime(rows[i].data_inicio, "%d/%m/%Y") + " | " + To_DateTime(rows[i].data_fim, "%d/%m/%Y") + " | " + std::to_string(rows[i].percentual / 12) << std::endl;
    // }
    // std::string holidays_file = "feriados.csv";
    // if (!file_exists(holidays_file))
    // {
    //     time_t date = time(&date);
    //     struct tm datetime = *localtime(&date);
    //     int current_year = datetime.tm_year + 1900;
    //     std::string json_holidays;
    //     int years = current_year - 1990;
    //     for (int year = current_year; year >= 1990; year--)
    //     {
    //         std::string uri = "https://brasilapi.com.br/api/feriados/v1/" + std::to_string(year);
    //         json_holidays = get(uri);
    //         holidays_file_content += parse_json_holidays(json_holidays);
    //     }

    //     create_csv(holidays_file, holidays_file_content);
    //     auto relevant_holidays = parse_holidays(holidays_file_content);
    //     std::string::difference_type holidays_count = std::count(holidays_file_content.begin(), holidays_file_content.end(), '\n');
    //     yield(rows[0].data_inicio, rows[0].data_fim, relevant_holidays, holidays_count, rows[0].percentual, rows[0].valor_investido);
        //std::string cdi = "https://investidor10.com.br/indices/cdi/";
        // auto cdi_page = get(cdi);
        // GumboOutput* parsed_response = gumbo_parse(cdi_page.c_str());
        // auto cdi_historic = parsecditable(parsed_response->root);
        // for(auto current_cdi : cdi_historic){
        //     std::cout << current_cdi.date.tm_mon << std::endl;
        //     std::cout << current_cdi.date.tm_mday << std::endl;
        //     std::cout << current_cdi.value << std::endl;

        // }
        // using json = nlohmann::json;
        // json cdi_table_json = cdi_historic;
        // Indexes* idx = new Indexes();
        // vector<Indexes::volatile_index> indexes = idx->createindexes();
        // string csv_data = idx->indextocsvfile(indexes);
        // string csv_name = "indices.csv";
        // createcsv(csv_name, csv_data);
        CLI cli;
        cli.run();
        // BufferedFileHandler handler("../indices.csv");
        // string read_data = handler.read();
        // auto data = parseindexers(read_data);
        // for(auto test: data){
        // int month = test.date.tm_mon + 1;
        // int year = test.date.tm_year + 1900;
        // string date = to_string(test.date.tm_mday) + "/" + to_string(month) + "/" + to_string(year);
        // cout << date<< endl;
        // cout << test.rate << endl;
        // }

    }
    // create_csv(holidays);
// }