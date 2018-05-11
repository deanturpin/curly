#include "curl.h"
#include <iostream>

void get_url_and_dump_tokens(const std::string url,
                             const bool application_id = true) {

  // Construct a CryptoCompare URL: prepend the domain and append the
  // application ID
  const auto cc = [&application_id](const std::string &url) {
    return tiny::curl(
        "https://min-api.cryptocompare.com/" + url +
        (application_id ? "&extraParams=https://github.com/deanturpin/arbitrage"
                        : ""));
  };

  // Request some prices and print the response
  const std::string response = cc(url);

  std::cout << response << "\n\n";

  // Print tokens
  for (const auto &t : tiny::json(response))
    std::cout << t.first << " : " << t.second << '\n';
}

int main() {

  get_url_and_dump_tokens("data/price?fsym=BTC&tsyms=USD,JPY,EUR,ETH");
  // get_url_and_dump_tokens("data/all/exchanges", true);
}
