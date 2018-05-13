#include "curly.h"
#include <iomanip>
#include <iostream>

std::string get_url_and_dump_tokens(const std::string url,
                                    const bool application_id = true) {

  // Construct a CryptoCompare URL: prepend the domain and append the
  // application ID
  const auto cc = [&application_id](const std::string &url) {
    return curly("https://min-api.cryptocompare.com/" + url +
                 (application_id
                      ? "&extraParams=https://github.com/deanturpin/curly"
                      : ""));
  };

  // Request some prices and print the tokens
  const std::string response = cc(url);
  std::stringstream ss;
  for (const auto &t : jsony(response))
    ss << t.first << '\t' << std::strtod(t.second.c_str(), NULL) << '\t';

  return ss.str();
}

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

  // Exchanges that offer BTC-USD
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

  // Request Bitcoin price from multiple exchanges
  std::vector<std::pair<double, std::string>> btc;
  for (const auto &e : exchanges)
    for (const auto &response :
         jsony(cc("data/price?fsym=BTC&tsyms=USD&e=" + e)))
      btc.push_back(
          std::make_pair(std::strtod(response.second.c_str(), NULL), e));

  std::cout << R"(
<!DOCTYPE html>

<meta charset="UTF-8">
<meta name="robots" content="index,follow" />
<link rel=icon href="favicon.ico" sizes="any">

<script>
onload = function(){
  var seconds = (10 * 60) - (new Date()).getSeconds();
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
a:link, a:visited { color: #ce905e; }
h1 {
  font-size: 100%;
  text-transform: uppercase;
  color: #f82f1f;
}
p.disclaimer { max-width: 700px; }
</style>
)";

  // Print sorted list of BTC coins from each exchange
  std::sort(std::begin(btc), std::end(btc));
  std::cout << "<h1>BTC-USD</h1><pre>\n";
  for (const auto &r : btc)
    std::cout << static_cast<unsigned long>(r.first) << '\t' << r.second << '\n';

  std::cout << "</pre>\n";
}
