#ifndef FILE_H
#define FILE_H
#include <string>
#include<iostream>
#include<fstream>
void create(std::string& file_name, std::string& content);
bool file_exists(std::string& file_name);
#endif