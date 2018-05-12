#include "curly.h"
#include <iomanip>
#include <iostream>

void get_url_and_dump_tokens(const std::string url,
                             const bool application_id = true) {

  // Construct a CryptoCompare URL: prepend the domain and append the
  // application ID
  const auto cc = [&application_id](const std::string &url) {
    return curly(
        "https://min-api.cryptocompare.com/" + url +
            (application_id
                 ? "&extraParams=https://github.com/deanturpin/arbitrage"
                 : ""));
  };

  // Request some prices and print the tokens
  const std::string response = cc(url);
  for (const auto &t : jsony(response))
    std::cout << t.first << '\t' << t.second << '\t' << response << '\n';
}

int main() {

  const std::vector<std::string> exchanges{
      "Bitfinex", "Cexio",     "TheRockTrading", "BTCE",          "Huobi",
      "BitBay",   "BitSquare", "Kraken",         "Coinbase",      "Poloniex",
      "BTCChina", "Quoine",    "BitFlip",        "CCEDK",         "ExtStock",
      "Coinroom", "CCEX",      "LakeBTC",        "OKCoin",        "Remitano",
      "TrustDEX", "LiveCoin",  "Gatecoin",       "itBit",         "QuadrigaCX",
      "HitBTC",   "Gemini",    "Coinsetter",     "Lykke",         "DSX",
      "Yobit",    "Coinfloor", "Bitlish",        "MonetaGo",      "Exmo",
      "Cryptsy",  "Coincap",   "Bitstamp",       "LocalBitcoins", "bitFlyer",
      "WavesDEX", "Abucoins",  "BitTrex",
  };

  for (const auto &e : exchanges)
    get_url_and_dump_tokens("data/price?fsym=BTC&tsyms=USD&e=" + e);
}
