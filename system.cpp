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
  const std::string response = cc("data/price?fsym=BTC&tsyms=USD,JPY,EUR,ETH");

  std::cout << "Raw response\n" << response << '\n';

  const auto tokens = tiny::json(response);

  // Print tokens
  std::cout << "\nTokens\n";
  for (const auto &t : tokens)
    std::cout << t.first << " : " << t.second << '\n';
}
