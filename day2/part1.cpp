#include <fstream>
#include <iostream>
#include <string>
#include <filesystem>
#include <algorithm>
#include <unordered_map>

std::unordered_map<std::string, int> mp {
  { "red",   12 },
  { "green", 13 },
  { "blue",  14 }
};

bool operator<(int num, const std::string s_val) {
  int val = std::stoi(s_val);
  return num < val;
}

int main(int argc, char* argv[]) {
  if (argc < 2) {
    std::cerr << "File not found!";
    exit(1);
  }

  std::filesystem::path p{argv[1]};
  std::ifstream file(p);

  int id_total = 0;
  if (file.is_open()) {
    std::string line;
    while(std::getline(file, line)) {
      bool is_possible = true;

      std::string curr_game_id; 
      int k = 0;
      for (int i = 0; i < line.size() && line[i] != ':'; i++) {
        if (std::isdigit(line[i])) {
          curr_game_id += line[i];
        } 
        ++k;
      }

      while (k < line.size()) {
        std::string num = "";
        std::string color = ""; 
        int j = k;
        while (j < line.size() && line[j] != ',' && line[j] != ';') {
          if (std::isdigit(line[j])) {
            num += line[j];  
          } else if (std::isalpha(line[j])) {
            color += line[j];
          }
          j++;
        }
        k = ++j; 


        std::cout << "NUM: " << num << "    Color: " << color << '\n';
        if (mp[color] < num) {
          std::cout << "Yes num is greater then the game amount\n";
          is_possible = false;
          break;
        }
      } 

      if (is_possible) {
        id_total += std::stoi(curr_game_id);
      }
    }
  } else {
    std::cerr << "File failed to open!";
    exit(1);
  }

  std::cout << "Total id count: " << id_total << '\n';
}
