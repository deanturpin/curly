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
  const std::vector<std::string> stage1_exchanges{
    "Bitstamp",
      "CoinDeal",
      "Kraken",
  };

  const std::vector<std::string> stage2_exchanges{
    "Coinroom",
      "BitSquare",
      "Abucoins",
  };

  // Request prices from multiple exchanges
  std::vector<double> stage1_prices;
  for (const std::string &name : stage1_exchanges) {

    const std::string to_symbol = "USD";
    const std::string response = cc("data/price?fsym=BTC&tsyms=" + 
                                    to_symbol + "&e=" + name);

    const double price =
      std::strtod(find_token(to_symbol, response).c_str(), NULL);

    if (price > 0.0)
      stage1_prices.push_back(price);
  }

  std::vector<double> stage2_prices;
  for (const std::string &name : stage2_exchanges) {

    const std::string to_symbol = "BTC";
    const std::string response = cc("data/price?fsym=ETH&tsyms=" + 
                                    to_symbol + "&e=" + name);

    const double price =
      std::strtod(find_token(to_symbol, response).c_str(), NULL);

    if (price > 0.0)
      stage2_prices.push_back(price);
  }

  const double transaction = 10000;
  std::vector<double> combined;
  for (const auto &p : stage1_prices)
    for (const auto &q : stage2_prices)
      combined.push_back(transaction / (1/q * transaction/p));

  std::sort(combined.begin(), combined.end());

  std::cout << "<div><pre>\n";
  for (const auto &c : combined)
    std::cout << c << '\n';
  std::cout << "</pre></div>\n";
}
