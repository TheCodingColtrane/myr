#ifndef FILE_PARSER_H
#define FILE_PARSER_H
#include <string>
#include <vector>
#include "indexes.h"
#include "investiments.h"

class Investiment;
std::vector<Indexes::volatile_index> parseindexers(std::string &rows);
std::vector<Investiment::investiments> parseinvestiments(std::string &rows);
std::vector<Investiment::holidays> parseholidays(std::string &rows);

#endif