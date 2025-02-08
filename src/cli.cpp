#include "../include/cli.h"
#include "../include/file.h"
#include "../include/file_parser.h"
#include "../include/date.h"
#include "../include/indexes.h"
#include "../include/bufferedfile.h"
#include "../include/investiments.h"

void CLI::checkforupdates(){
    bool * required_files = new bool[3];
    std::string *file_names = new std::string[3];
    file_names[0] = "../indices.csv";
    file_names[1] = "../investiments.csv";
    file_names[2] = "../holidays.csv";
    required_files[0] = file_exists(file_names[0]);
    required_files[1] = file_exists(file_names[1]);
    required_files[2] = file_exists(file_names[2]);
    delete[] file_names;
    if(!required_files[0] || !required_files[1] || !required_files[2]){
        delete[] required_files;
        std::string holidays_csv_data = getholidays();
        Indexes* idx = new Indexes();
        std::vector<Indexes::volatile_index> indexes = idx->createindexes();
        std::string index_csv_data = idx->indextocsvfile(indexes);
        std::string index_csv_name = "indices.csv";
        std::string holidays_csv_name = "holidays.csv";
        create(holidays_csv_name, holidays_csv_data);
        create(index_csv_name, index_csv_data);
        time_t date = time(&date);
        struct tm datetime = *localtime(&date);
        int year = datetime.tm_year + 1900;
        int month = datetime.tm_mon + 1;
        int day = datetime.tm_mday;
        std::string today = std::to_string(year) + "-" + std::to_string(month) + "-" + std::to_string(day)+ 'T' + "00:00:00.00Z"; 
        std::string json_config = "{\n \t \"configs\": {\n \t \t \"lastUpdate\": \""+ today +"\",\n \t \t \"country\":  \"Brazil\"\n \t}\n }";
        std::string json_config_file = "config.json";
        create(json_config_file, json_config);
        checked_for_updates = true;

    }


}

void::CLI::profit(){
    BufferedFileHandler investiments_handler("../investiments.csv");
    BufferedFileHandler holidays_handler("../holidays.csv");
    std::string investiments_data = investiments_handler.read();
    std::string holidays_data = holidays_handler.read();
    auto investiments = parseinvestiments(investiments_data);
    auto holidays = parseholidays(holidays_data);
    Investiment *investiment = new Investiment();
    for(auto current_investiment : investiments){
        auto money = investiment->profit(current_investiment, holidays);
        std::cout << "Seu dinheiro rendeu: " + std::to_string(money[0]) + " de: " + std::to_string(money[1]) + " com imposto tirado na fonte " + std::to_string(money[2]) << std::endl;
    }

}


void CLI::setupcommands() {
        commands["help"] = {
            "Display all available commands",
            [this]() { showhelp(); }
        };

        commands["profit"] = {
            "Calculate potential profit from investment",
            [this]() { profit(); }
        };

        // commands["roi"] = {
        //     "Calculate Return on Investment (ROI)",
        //     [this]() { calculateROI(); }
        // };

        // commands["compound"] = {
        //     "Calculate compound interest over time",
        //     [this]() { calculateCompound(); }
        // };

        // commands["break-even"] = {
        //     "Calculate break-even point",
        //     [this]() { calculateBreakEven(); }
        // };

        commands["exit"] = {
            "Exit the program",
            [this]() { running = false; }
        };
}

void CLI::showhelp() {
        std::cout << "\nAvailable Commands:\n";
        std::cout << "==================\n";
        for (const auto& [cmd, info] : commands) {
            std::cout << std::left << std::setw(15) << cmd 
                     << info.description << "\n";
        }
        std::cout << "\n";
    }

void CLI::run(){
        if(!checked_for_updates) checkforupdates();
        std::cout << "Welcome to Investment Calculator!\n";
        std::cout << "Type 'help' to see available commands.\n\n";

        std::string input;
        while (running) {
            std::cout << "> ";
            std::getline(std::cin, input);

            auto it = commands.find(input);
            if (it != commands.end()) {
                it->second.handler();
            } else {
                std::cout << "Unknown command. Type 'help' for available commands.\n";
            }
        }
    }