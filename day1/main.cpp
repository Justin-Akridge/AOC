#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include <algorithm>

std::vector<std::string> numbers {
  "one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten"
};

int main(int argc, char* argv[]) {
  if (argc < 2) {
    std::cerr << "error: file expected!!";
    exit(1);
  }
  std::filesystem::path p { argv[1] };
  std::ifstream file(p);
  //std::ifstream file("input.txt");
  
  int val = 0;
  if (file.is_open()) {
    std::string line;
    while (std::getline(file, line)) {
      std::vector<char> v(line.size(), '#');

      for (int i = 0; i < numbers.size(); i++) {
        int found_first = line.find(numbers[i]);
        int found_last = line.rfind(numbers[i]);
        std::cout << found_first << ' ' << found_last << '\n';

        if (found_first != std::string::npos) {
          v[found_first] = (i + 1) + '0';
        }
        
        if (found_last != std::string::npos) {
          v[found_last] = (i + 1) + '0';
        }
      }

      for (int i = 0; i < line.size(); i++) {
        if (std::isdigit(line[i])) {
          v[i] = line[i];
        }
      }

      //for (auto &num : v) std::cout << num;

      std::string res = "";
      for (int i = 0; i < v.size(); i++) {
        if (v[i] != '#') {
          res += v[i];
          break;
        } 
      }

      for (int i = v.size() - 1; i >= 0; i--) {
        if (v[i] != '#') {
          res += v[i];
          break;
        } 
      }
      
      int result = stoi(res);
      std::cout << "Result = " << res << " to int : " <<  result << '\n';
      
      val += result;

    }
  } else {
    std::cerr << "Error: file failed to open!!";
  }
  std::cout << "VAL: " << val << '\n';
}
