#include "curly.h"
#include <iomanip>
#include <iostream>
#include <iterator>

int main() {

  // Construct a CryptoCompare URL: prepend the domain and append the
  // application ID
  const auto application_id = true;
  const auto cc = [&application_id](const std::string &url) {
    return curly("https://min-api.cryptocompare.com/" + url +
                 (application_id
                      ? "&extraParams=https://github.com/deanturpin/curly"
                      : ""));
  };

  // Exchanges
  const std::vector<std::string> stage1_exchanges{
      "HitBTC",   "Bitfinex", "Cexio",    "Quoine",  "ExtStock", "BitFlip",
      "Coinbase", "Gatecoin", "Lykke",    "BitTrex", "Bitstamp", "Coinroom",
      "LiveCoin", "Kraken",   "Exmo",     "DSX",     "Bitlish",  "Gemini",
      "CCEX",     "Coincap",  "Poloniex", "BitBay",  "Yobit",    "WavesDEX",
  };

  const std::string from_symbol = "ETH";
  const std::string to_symbol = "USD";

  // Fetch prices for each exchange
  std::vector<std::pair<double, std::string>> stage1_prices;
  for (const std::string &name : stage1_exchanges) {

    const std::string response = cc("data/price?fsym=" + from_symbol +
                                    "&tsyms=" + to_symbol + "&e=" + name);

    const double price =
        std::strtod(find_token(to_symbol, response).c_str(), NULL);

    // Only store non-zero prices
    if (price > 0.0)
      stage1_prices.push_back({price, name});
  }

  // Print HTML header
  std::cout << std::ifstream("template.html").rdbuf();

  // Sort the prices before calculating the combinations
  std::sort(stage1_prices.begin(), stage1_prices.end());
  std::reverse(stage1_prices.begin(), stage1_prices.end());

  // Print the combined prices
  if (!stage1_prices.empty()) {
    std::cout << std::fixed << std::setprecision(0);
    std::cout << "<div>\n";
    std::cout << "<h2>" << from_symbol << "-" << to_symbol << " "
              << 100.0 * stage1_prices.front().first /
                     stage1_prices.back().first
              << " %</h2>\n";

    std::cout << "<pre>\n";
    for (const auto &p : stage1_prices)
      std::cout << p.first << '\t' << p.second << '\n';

    std::cout << "</pre></div>\n";
  }
}
