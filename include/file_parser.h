#ifndef FILE_PARSER_H
#define FILE_PARSER_H
#include <string>
#include <vector>
#include "indexes.h"
struct investiments {
   std::string nome;
   double percentual;
   double valor_investido;
   time_t data_inicio;
   time_t data_fim; 
   int investiments_count;
};

struct holidays {
   std::string name;
   time_t date; 
};

investiments *parse_investiments(std::string &rows);
holidays *parse_holidays(std::string &rows);
std::vector<Indexes::volatile_index> parseindexers(std::string &rows);

#endif