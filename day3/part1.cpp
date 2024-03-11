#include <fstream>
#include <iostream>
#include <filesystem>
#include <vector>
#include <regex>
#include <cassert>

const std::regex pattern("[^a-zA-Z0-9.]+");
bool check(int col_start, int col_end, int row, std::vector<std::string>& lines) {
  auto is_special = [](const std::string& s){
    if (std::regex_search(s, pattern)) { return true; }
    else { return false; }
  };

  assert(row >= 0 && row <= lines.size() - 1);
  assert(col_start >= 0 && col_start <= lines[row].size()-1 && col_end >= col_start && col_end <= lines[row].size()-1);

  int len = col_end - col_start + 1;
  if (row == 0) {
    if (col_start == 0) {
      std::string s = lines[row+1].substr(0, len + 1) + lines[row].substr(0, len + 1);
      if (is_special(s)) { return true; }
      else { return false; }
    } else if (col_end == lines[row].size() - 1) {
      std::string s = lines[row+1].substr(col_start-1, len + 1) + lines[row].substr(col_start - 1, 1);
      if (is_special(s)) return true;
      else return false;
    } else {
      std::string s = lines[row].substr(col_start - 1, len + 2) + lines[row + 1].substr(col_start - 1, len + 2);
      if (is_special(s)) return true;
      else return false;
    }
  
  } else if (row == lines.size() - 1) {
    if (col_start == 0) {
      std::string s = lines[row-1].substr(col_start, len + 1) + lines[row].substr(col_start, len + 1);
      if (is_special(s)) return true;
      else return false;
    } else if (col_end == lines[row].size() - 1) {
      std::string s = lines[row-1].substr(col_start-1, len + 1) + lines[row].substr(col_start - 1, 1);
      if (is_special(s)) return true;
      else return false;
    } else {
      std::string s = lines[row - 1].substr(col_start - 1, len + 2) + lines[row].substr(col_start - 1, len + 2);
      if (is_special(s)) return true;
      else return false;
    }
  } else {
    if (col_start == 0) {
      std::string s = lines[row-1].substr(col_start, len + 1) + lines[row].substr(col_start, len + 1) + lines[row+1].substr(col_start, len + 1);
      if (is_special(s)) { return true; }
      else return false;
    } else if (col_end == lines[row].size() - 1) {
      std::string s = lines[row-1].substr(col_start-1, len + 1) + lines[row+1].substr(col_start - 1, len + 1) + lines[row].substr(col_start - 1, len + 1);
      if (is_special(s)) { return true; }
      else return false;
    } else {
      std::string s = lines[row].substr(col_start - 1, len + 2) + lines[row - 1].substr(col_start - 1, len + 2) + lines[row+1].substr(col_start - 1, len + 2);
      if (is_special(s)) return true;
      else return false;
    }
  }
  return true;
}

void get_lines(std::ifstream& file, std::vector<std::string>& lines) {
  if (file.is_open()) {
    std::string line;
    while (std::getline(file, line)) {
      lines.push_back(line);
    }
  } else {
    std::cerr << "failed to open file";
    exit(1);
  }
}


int res(std::vector<std::string>& lines) {
  int total = 0;
  for (int i = 0; i < lines.size(); i++) {
    for (int j = 0; j < lines[i].size(); j++) {
      if (std::isdigit(lines[i][j])) {
        int start = j;
        int end = j;
        while (std::isdigit(lines[i][end])) {
          ++end;
        } 
        --end;
        int num = std::stoi(lines[i].substr(start, end - start + 1));
        if (check(start, end, i, lines)) {
          total += num;
        }
        j = end;
      }
    }
  }
  return total;
}

int main(int argc, char* argv[]) {
  if (argc < 2) {
    std::cerr << "Error: Missing file";
    exit(1);
  }
  std::filesystem::path p{argv[1]};
  std::ifstream file(p);
  std::vector<std::string> lines;
  get_lines(file, lines);
  file.close();
  int ret = res(lines);
  std::cout << "Result: " << ret << '\n';
  // test for row 0
  std::vector<std::string> test;

  test = {
    "467..114..", 
    "...*......",
    "..35..633.",
    "......#...",
    "617*......",
    ".....+.58.",
    "..592.....",
    "......755.",
    "...$.*....",
    ".664.598.."
  };
  assert(res(test) == 4361);

  test = {
    "..*...",
    "...1..",
    "......"
  };
  assert(res(test) == 1);

  test = {
    "...*..",
    "...1..",
    "......"
  };
  assert(res(test) == 1);

  test = {
    "....*.",
    "...1..",
    "......"
  };
  assert(res(test) == 1);
  test = {
    "......",
    "...1*.",
    "......"
  };
  assert(res(test) == 1);
  test = {
    "......",
    "...1..",
    "....*."
  };
  assert(res(test) == 1);
  test = {
    "......",
    "...1..",
    "...*.."
  };
  assert(res(test) == 1);
  test = {
    "......",
    "...1..",
    "..*..."
  };
  assert(res(test) == 1);
  test = {
    "......",
    "..*1..",
    "......"
  };
  assert(res(test) == 1);
  test = {
    "......",
    "...1..",
    ".....*"
  };
  assert(res(test) == 0);
  test = {
    "10....",
    "..*..."
  };
  assert(res(test) == 10);

  test = {
    "....10",
    "...*.."
  };
  assert(res(test) == 10);

  test = {
    "...10..",
    ".*....."
  };
  assert(res(test) == 0);

  // test for row 1
  test = {
    "&..&...",
    "1......",
    ".*....."
  };
  assert(res(test) == 1);

  test = {
    "&..&...",
    ".....1.",
    ".*....."
  };
  assert(res(test) == 0);

  test = {
    "&..&...",
    ".....11",
    ".*..*.."
  };
  assert(res(test) == 11);

  test = {
    "&..&.*.",
    ".....11",
    ".*.*111"
  };
  assert(res(test) == 122);

  test = {
    "&..&.*.",
    ".....11",
    "1*.*111"
  };
  assert(res(test) == 123);
  
  test = {
    "&..&.*.",
    "....*..",
    "1*33..."
  };
  assert(res(test) == 34);

  test = {
    "&..&.*.",
    "....*..",
    "1*....1"
  };
  assert(res(test) == 1);

  test = {
    ".1.......1..",
    "....1..*1...",
    "...*.....1.."
  };
  assert(res(test) == 2);
}

