#include "curl.h"
#include <iostream>

int main() {

  const std::string url =
      "https://min-api.cryptocompare.com/data/all/exchanges"
      "?extraParams=https://github.com/deanturpin/arbitrage";

  const auto response = curl(url);
  std::cout << response << '\n';
}
