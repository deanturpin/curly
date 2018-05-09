#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

int main() {

  std::ifstream in("pairs.csv");

  using currency_pairs = std::map<std::string, std::vector<std::string>>;

  currency_pairs pairs;

  std::string line;
  while (getline(in, line)) {
    std::stringstream ss(line);
    std::string exchange, from, to;
    ss >> exchange >> from >> to;
    pairs[from + "-" + to].push_back(exchange);
  }

  std::cout << pairs.size() << " pairs\n";

  for (const auto &p : pairs) {
    std::cout << p.first;
    for (const auto &e : p.second)
      std::cout << ' ' << e;

    std::cout << '\n';
  }
}
