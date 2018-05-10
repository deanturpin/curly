#include "curl.h"
#include <iostream>

int main() {

  // Construct a CryptoCompare URL: prepend the domain and append the
  // application ID
  const auto cc = [](const std::string &url) {
    const std::string domain = "https://min-api.cryptocompare.com/";
    const std::string applic =
        "&extraParams=https://github.com/deanturpin/arbitrage";
    return domain + url + applic;
  };

  // Request some prices and print the response
  const std::string url = cc("data/price?fsym=BTC&tsyms=USD,JPY,EUR");
  const auto response = curl(url);

  std::cout << response << '\n';
}
