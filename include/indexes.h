#ifndef INDEXES_H
#define INDEXES_H
#include <time.h>
#include <vector>
#include <string>
class Indexes {
    public:
struct volatile_index {
    tm date;
    float rate;
    int type;
};
std::vector<volatile_index> createindexes(bool update = false);
std::string indextocsvfile(std::vector<Indexes::volatile_index> &index_data);

// std::vector<volatile_index> indexes;
};
// 0 - SELIC, 1 - IPCA, 2 - CDI


//https://api.bcb.gov.br/dados/serie/bcdata.sgs.16122/dados?formato=json
//https://api.bcb.gov.br/dados/serie/bcdata.sgs.1178/dados?formato=json;
//https://api.bcb.gov.br/dados/serie/bcdata.sgs.4391/dados?formato=json
#endif