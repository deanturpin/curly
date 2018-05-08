#include <string>
#include <vector>

#include "prices.h"
#include <iostream>

int main() {

  std::cout << exchanges.size() << " exchanges\n";
  for (const auto &e : exchanges)
    std::cout << e.name << " - " << e.symbols.size() << '\n';
}
