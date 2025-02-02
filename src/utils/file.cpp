#include "../../include/file.h"
#include <filesystem>
#include "../../include/bufferedfile.h"

void  read_csv(std::string& file_name, std::string& content){
  std::ifstream file("../" + file_name);
  if (!file.is_open())
  {
    std::cerr << "Error opening file";
  }
  std::string next_row, rows;
  int row_count = 0;
  while (getline(file, next_row))
  {
    std::string aux_row = next_row;
    if (row_count) rows += aux_row + ';';
    else rows = aux_row + ';';

    
    row_count++;
  }
  content = rows;
  file.close();
}

void new_csv_row(std::string& file_name, std::string& content)
{
  std::ofstream file("../" + file_name);
  if (!file.is_open())
  {
    std::cerr << "Error opening file";
    return;
  } 
  file << content;
  std::cout << "Investimento salvo.";
}


void create(std::string& file_name, std::string& content){

  BufferedFileHandler handler("../" + file_name);
  handler.write(content);
  std::cout << "file succefully created.";
  return;
}

bool file_exists(std::string& file_name){
 bool file_exists = std::filesystem::exists(file_name);
  if(file_exists) return true;
  return false;
}

