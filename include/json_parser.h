#ifndef JSON_PARSER_H
#define JSON_PARSER_H
#include <string>
#include <simdjson.h>
#include <vector>
#include "indexes.h"
using namespace std;
string parse_json_holidays(string &json);
void parse_json_indices(string &json, vector<Indexes::volatile_index> & indexes, int &type);
#endif