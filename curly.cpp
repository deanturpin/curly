#include "curly.h"
#include <iomanip>
#include <iostream>

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

  // Print HTML header
  std::cout << R"(
<!DOCTYPE html>

<meta charset="UTF-8">
<meta name="robots" content="index,follow" />
<link rel=icon href="favicon.ico" sizes="any">

<script>
onload = function(){
  var seconds = (5 * 60) - (new Date()).getSeconds();
  setTimeout(function() {
    window.location.reload();
  }, seconds * 1000);
}
</script>

<style>
body {
  font-family: sans-serif;
  background-color: #c2eef1;
  color: black;
  padding: 40px;
}
h1 { color: #ce905e; }
h2 { color: #f82f1f; }
</style>

<h1>curly</h1>
)";

  // Exchanges that offer BTC-USD
  const std::vector<std::string> exchange_names{
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

  std::vector<std::pair<std::string, std::vector<double>>> exchanges;

  const std::string fiat = "USD";
  for (const std::string &coin : {"BTC", "ETH", "BCH"}) {

    // Request prices from multiple exchanges
    for (const std::string &name : exchange_names) {

      const std::string response =
        cc("data/price?fsym=" + coin + "&tsyms=" + fiat + "&e=" + name);

      const double price =
        std::strtod(find_token(fiat, response).c_str(), NULL);

      const auto it =
        std::find_if(exchanges.begin(), exchanges.end(),
                     [&name](const auto &e) { return e.first == name; });

      if (it == exchanges.cend())
        exchanges.push_back(std::make_pair(name, std::vector<double>({price})));
      else
        it->second.push_back(price);
    }
  }

  // Print sorted lists of prices from each exchange
  std::sort(exchanges.begin(), exchanges.end(),
            [](const auto &a, const auto &b) {
            return a.second.front() > b.second.front();});

  std::cout << "<div><h2>USD</h2><pre>\nBTC\tETH\tBCH\tExchange\n";
  for (const auto &e : exchanges) {
    for (const auto &p : e.second)
      std::cout << p << '\t';
    std::cout << e.first << '\n';
  }

  std::cout << "</pre></div>\n";
}
