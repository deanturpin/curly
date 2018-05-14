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

  const std::vector<std::string> stage2_exchanges{
      "Bitstamp", "CoinDeal",      "Kraken",    "Lykke",          "LakeBTC",
      "MonetaGo", "itBit",         "BTCE",      "TheRockTrading", "Paymium",
      "Coinroom", "BitSquare",     "Abucoins",  "Cexio",          "LiveCoin",
      "DSX",      "LocalBitcoins", "Exmo",      "BitMarket",      "HitBTC",
      "ExtStock", "Yacuna",        "Coinfloor", "Quoine",         "Bitfinex",
      "BitBay",   "Gatecoin",      "Cryptsy",   "BitFlip",        "Bitlish",
      "WavesDEX", "CCEDK",         "Coinbase",
  };

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

  // Calculate all combinations of prices from all exchanges
  decltype(stage1_prices) combined;
  auto p = stage1_prices.cbegin();
  auto q = stage1_prices.crbegin();

  for (; p != stage1_prices.cend(); ++p, ++q) 
    combined.push_back({q->first / p->first,
                       p->second + " " + std::to_string(p->first) + " > " +
                       q->second + " " + std::to_string(q->first)});

  // Order by final price
  std::sort(combined.begin(), combined.end());
  std::reverse(combined.begin(), combined.end());

  // Print HTML header
  std::cout << std::ifstream("index.html").rdbuf();

  // Print the combined prices
  std::cout << "<div>\n";
  std::cout << "<h2>USD > BTC > USD</h2>\n";
  std::cout << "<pre>\n";
  std::cout << std::fixed << std::setprecision(0);
  for (const auto &c : combined)
    std::cout << 100.0 * c.first << " %\t" << c.second << '\n';
  std::cout << "</pre></div>\n";
}
