#include <string>
#include <vector>
#include <iostream>
#include <fstream>

int main() {

  std::ifstream in("pairs.csv");

  std::string line;
  std::vector<std::string> pairs;
  while (getline(in, line))
    pairs.emplace_back(line);

  std::cout << pairs.size() << " pairs\n";
}
