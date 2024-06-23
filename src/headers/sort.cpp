#include <iostream>
#include <filesystem>

std::string fileExtension(std::string path, std::string path_2, std::string extension = "null"){
  int end;
  if (extension != "null") {
    end = path.size() - path_2.size() + extension.size();
    }
  else {
    end = path.size() - path_2.size();
    }
  path.erase(path.begin() + 0, path.end() - end + 1);
  return path;
}

std::string append(std::string user_path, std::string file, std::string extension){
  return user_path.append("/" + fileExtension(file, file, extension));
  }

void createDir(std::string user_path){
  for(auto entry : std::filesystem::directory_iterator(user_path)){
    std::string file = entry.path().generic_string();
    std::string extension = entry.path().extension().generic_string();
    if (extension != "") {std::filesystem::create_directory(append(user_path, file, extension));}
  }
}

void move(std::string path){
  for(auto entry : std::filesystem::directory_iterator(path)){
    std::string file = entry.path().generic_string();
    std::string extension = entry.path().extension().generic_string();
    if(entry.path().extension().generic_string() != ""){
      std::filesystem::rename(file, append(path, file, extension).append("/" + fileExtension(file, path)));
      }
  }
}

void fileSort(std::string path = std::filesystem::current_path().generic_string()){
  createDir(path);
  move(path);
}