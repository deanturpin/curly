#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

int main() {

  std::ifstream in("tmp/markets.csv");

  struct exchange {
    std::string name;
    std::vector<std::vector<std::string>> markets;
  };

  std::vector<exchange> exchanges;

  std::string line;
  while (getline(in, line)) {

    std::stringstream ss(line);
    std::string name, symbol;

    // Extract exchange name and market symbols
    ss >> name;
    std::vector<std::string> symbols;
    while (ss >> symbol)
      symbols.push_back(symbol);

    // Check if we already have an entry for this exchange
    auto it = std::find_if(exchanges.begin(), exchanges.end(),
                           [&name](const auto &m) { return m.name == name; });

    // Not market then create a new one and insert it
    if (it == exchanges.end()) {

      // Append an empty exchange
      exchanges.push_back({name, {}});

      // Move iterator to last element added
      it = std::prev(exchanges.end());
    }

    // Update existing or new entry
    it->markets.push_back(symbols);
  }

  // Sort exchanges by number of markets offered
  std::sort(exchanges.begin(), exchanges.end(),
            [](const auto &lhs, const auto &rhs) {
              return lhs.markets.size() < rhs.markets.size();
            });

  // Report exchange summary
  std::cout << exchanges.size() << " exchanges\n";
  for (const auto &e : exchanges)
    std::cout << e.name << ' ' << e.markets.size() << '\n';
}
