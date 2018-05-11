#include "curl.h"
#include <iostream>

int main() {

  // Construct a CryptoCompare URL: prepend the domain and append the
  // application ID
  constexpr auto cc = [](const std::string &url) {
    return tiny::curl("https://min-api.cryptocompare.com/" + url +
           "&extraParams=https://github.com/deanturpin/arbitrage");
  };

  // Request some prices and print the response
  std::cout << cc("data/price?fsym=BTC&tsyms=USD,JPY,EUR");
}
