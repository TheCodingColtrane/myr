#include <iostream>
#include <string>
#include <map>
#include <functional>
#include <iomanip>
#include <sstream>
#include <vector>

class CLI {
private:
    struct Command {
        std::string description;
        std::function<void()> handler;
    };

    std::map<std::string, Command> commands;
    bool running = true;
    bool checked_for_updates = false;
    // Helper function to get validated numerical input
    double getValidatedInput(const std::string& prompt) {
        double value;
        std::string input;
        while (true) {
            std::cout << prompt;
            std::getline(std::cin, input);
            
            try {
                value = std::stod(input);
                if (value < 0) {
                    std::cout << "Please enter a non-negative number.\n";
                    continue;
                }
                break;
            } catch (...) {
                std::cout << "Invalid input. Please enter a valid number.\n";
            }
        }
        return value;
    }

public:
    void showcommands();
    void showhelp();
    void run();
    void checkforupdates();
    void profit();
    void setupcommands();
    CLI(){
        setupcommands();
    }
};