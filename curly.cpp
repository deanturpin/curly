#include "curly.h"

void get_url_and_dump_tokens(const std::string url,
                             const bool application_id = true) {

  // Construct a CryptoCompare URL: prepend the domain and append the
  // application ID
  const auto cc = [&application_id](const std::string &url) {
    return curly(
        "https://min-api.cryptocompare.com/" + url +
        (application_id ? "&extraParams=https://github.com/deanturpin/arbitrage"
                        : ""));
  };

  // Request some prices and print the response
  const std::string response = cc(url);

  std::puts(response.c_str());

  // Print tokens
  for (const auto &t : jsony(response))
    std::puts((t.first + '\t' + t.second).c_str());

  for (const auto &t : jsony2(response))
    std::puts((t.first + '\t' + t.second).c_str());
}

int main() {

  get_url_and_dump_tokens("data/price?fsym=BTC&tsyms="
                          "USD,JPY,EUR,ETH,LTC,DASH,BCH");
  // get_url_and_dump_tokens("data/all/exchanges", true);
}
