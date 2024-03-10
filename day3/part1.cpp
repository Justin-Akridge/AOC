#include <fstream>
#include <iostream>
#include <filesystem>
#include <vector>

int main(int argc, char* argv[]) {
  if (argc < 2) {
    std::cerr << "Error: Missing file";
    exit(1);
  }

  std::filesystem::path p{argv[1]};
  std::ifstream file(p);
  if (file.is_open()) {
    std::vector<std::vector<char>> lines(140, std::vector<char>(140));
    int i = 0;
    int j = 0;
    while (char c = file.get()) {
      lines[i][j] = c;
      i++;
      j++;
      if (j == 140) {
        ++i;
        j = 0;
      }
    }
    for (int i = 0; i < lines.size(); i++) {
      for (int j = 0; j < lines[i].size(); j++) {
        std::cout << lines[i][j] << '\n';
      }
    }
  } else {
    std::cerr << "Failed to open file";
    exit(1);
  }
}
