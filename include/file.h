#ifndef FILE_H
#define FILE_H
#include <string>
#include<iostream>
#include<fstream>
void read_csv(std::string& file_name, std::string& content);
void new_csv_row(std::string& file_name, std::string& content);
void create(std::string& file_name, std::string& content);
bool file_exists(std::string& file_name);
#endif