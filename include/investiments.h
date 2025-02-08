#ifndef INVESTIMENTS_H
#define INVESTIMENTS_H
#include <string>
#include <vector>
class Investiment
{
public:
    struct investiments
    {
        std::string asset_name;
        float value;
        float monthly_contributions;
        float rate;
        time_t starting_date;
        time_t ending_date;
    };
    struct holidays
    {
        std::string name;
        time_t date;
    };
    float roi();
    float* profit(investiments investiment, std::vector<holidays> holiday);
};

// void delete_investiment();
// void update_investiment();
#endif