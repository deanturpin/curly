#include "curl.h"
#include <iostream>

int main() {

  const std::string url =
    "https://min-api.cryptocompare.com/data/price?fsym=BTC&tsyms=USD,JPY,EUR";

  const auto response = curl(url);
  std::cout << response << '\n';
}
