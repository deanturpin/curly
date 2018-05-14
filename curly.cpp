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
                          : ""),
                 true);
  };

  // Exchanges that offer BTC-USD
  const std::vector<std::string> stage1_exchanges{
      "BitBay",    "Bitstamp",   "TrustDEX",       "itBit",
      "BTCChina",  "Kraken",     "TheRockTrading", "Poloniex",
      "Cexio",     "CCEDK",      "BitSquare",      "DSX",
      "Coinbase",  "LakeBTC",    "Coinroom",       "Gemini",
      "Coincap",   "Bitfinex",   "MonetaGo",       "Quoine",
      "Lykke",     "BitFlip",    "Huobi",          "Gatecoin",
      "Abucoins",  "Cryptsy",    "BTCE",           "HitBTC",
      "bitFlyer",  "Remitano",   "WavesDEX",       "CCEX",
      "BitTrex",   "Exmo",       "Yobit",          "OKCoin",
      "Coinfloor", "QuadrigaCX", "ExtStock",       "Coinsetter",
      "Bitlish",   "LiveCoin",   "LocalBitcoins",
  };

  // Fetch prices for each exchange
  std::vector<std::pair<double, std::string>> stage1_prices;
  for (const std::string &name : stage1_exchanges) {

    const std::string to_symbol = "USD";
    const std::string response =
        cc("data/price?fsym=BTC&tsyms=" + to_symbol + "&e=" + name);

    const double price =
        std::strtod(find_token(to_symbol, response).c_str(), NULL);

    if (price > 8000.0 && price < 10000.0)
      stage1_prices.push_back({price, name});
  }

  // Print HTML header
  std::cout << std::ifstream("index.html").rdbuf();

  // Print the combined prices
  std::cout << "<div>\n";
  std::cout << "<h2>USD > BTC > USD</h2>\n";
  std::cout << "<pre>\n";
  std::cout << std::fixed << std::setprecision(0);

  // Sort the prices before calculating the combinations
  std::sort(stage1_prices.begin(), stage1_prices.end());

  // Calculate all combinations of prices
  auto p = stage1_prices.cbegin();
  auto q = stage1_prices.crbegin();

  for (; p != stage1_prices.cend() && q != stage1_prices.crend(); ++p, ++q)
    std::cout << 100.0 * q->first / p->first << " %\t" <<
                        p->second << " " << p->first << " > " +
                            q->second << " " << q->first << '\n';

  std::cout << "</pre></div>\n";
}
