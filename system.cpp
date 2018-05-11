#include "curl.h"
#include <iostream>
#include <regex>

int main() {

  // Construct a CryptoCompare URL: prepend the domain and append the
  // application ID
  constexpr auto cc = [](const std::string &url) {
    return tiny::curl("https://min-api.cryptocompare.com/" + url +
                      "&extraParams=https://github.com/deanturpin/arbitrage");
  };

  // Request some prices and print the response
  const std::string response = cc("data/price?fsym=BTC&tsyms=USD,JPY,EUR,ETH");

  std::cout << "response: " << response << '\n';

  std::cout << "comma split\n";
  std::regex tokens(R"([{},:"]+)");
  std::copy(std::sregex_token_iterator(response.begin(), response.end(),
                                       tokens, -1),
            std::sregex_token_iterator(),
            std::ostream_iterator<std::string>(std::cout, "\n"));
}
