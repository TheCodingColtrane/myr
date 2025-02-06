#include "../../include/file.h"
#include <filesystem>
#include "../../include/bufferedfile.h"


void create(std::string& file_name, std::string& content){

  BufferedFileHandler handler("../" + file_name);
  handler.write(content);
  std::cout << "file succefully created." << std::endl;
  return;
}

bool file_exists(std::string& file_name){
 bool file_exists = std::filesystem::exists(file_name);
  if(file_exists) return true;
  return false;
}

