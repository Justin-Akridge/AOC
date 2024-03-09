#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <filesystem>
#include <algorithm>
#include <unordered_map>

std::string colors[] = {"blue", "green", "red"};

int main(int argc, char* argv[]) {
  if (argc < 2) {
    std::cerr << "File not found!";
    exit(1);
  }

  std::filesystem::path p{argv[1]};
  std::ifstream file(p);

  int ret = 0;
  if (file.is_open()) {
    std::string line;
    while(std::getline(file, line)) {
      int k = line.find(':');


      std::vector<int> indexes;
      int curr = 0;
      while (true) {
        int found = line.find(';', curr); 
        if (found == std::string::npos) break;
        indexes.emplace_back(found);
        curr = found + 1;
      }

      std::vector<std::string> games(indexes.size());
      for (int i = 0; i < indexes.size(); i++) {
        games[i] = line.substr(k + 1, indexes[i] - k - 1);
        k = indexes[i];
      }

      std::unordered_map<std::string, int> mp;
      int blue = games[i].find("blue"); 
      if (blue != std::string::npos) {
        mp["blue"] = blue;
      }

      int green = games[i].find("green");
      if (green != std::string::npos) {
        mp["green"] = green;
      }

      int red = games[i].find("red");
      if (red != std::string::npos) {
        mp["red"] = red;
      }
      
      int pos[3];
      for (auto it = mp.begin(); it != mp.end(); it++) {
        if (
      }
      if (mp["blue"] > mp["red"] && mp["blue"] > mp["green"]) {
        pos[0]

      //while (k < line.size()) {
      //  std::string num = "";
      //  std::string color = ""; 
      //  int j = k;
      //  while (j < line.size() && line[j] != ',' && line[j] != ';') {
      //    if (std::isdigit(line[j])) {
      //      num += line[j];  
      //    } else if (std::isalpha(line[j])) {
      //      color += line[j];
      //    }
      //    j++;
      //  }

      //  int inum = std::stoi(num);

      //  if (mp.find(color) == mp.end()) {
      //    mp[color] = inum;
      //  } else {
      //    if (mp[color] < inum) {
      //      mp[color] = inum;
      //    }
      //  }
      //  k = ++j; 
      //} 

      //int total = 1;
      //for (auto it = mp.begin(); it != mp.end(); it++) {
      //  total *= it->second;
      //}
      //ret += total;
    }
  } else {
    std::cerr << "File failed to open!";
    exit(1);
  }

  std::cout << "res: " << ret << '\n';
}

