#include "curly.h"
#include <iomanip>
#include <iostream>
#include <iterator>
#include <numeric>
#include <vector>

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


  const auto get_exchanges = [](){
    std::ifstream in("exchanges.txt");

    std::vector<std::string> e;
    std::string name;
    while (in >> name)
      e.push_back(name);

    return e;
  };

  // Exchanges
  const std::vector<std::string> &stage1_exchanges = get_exchanges();

  std::cout << "Using " << stage1_exchanges.size() << " exchanges.\n";

  for (const auto &from_symbol :
       std::vector<std::string>({"ETH", "BTC", "BCH", "LTC"})) {

    const std::string to_symbol = "USD";

    // Fetch prices for each exchange
    std::vector<std::pair<double, std::string>> stage1_prices;
    for (const std::string &name : stage1_exchanges) {

      const std::string response = cc("data/price?fsym=" + from_symbol +
                                      "&tsyms=" + to_symbol + "&e=" + name);

      const double price =
          std::strtod(find_token(to_symbol, response).c_str(), NULL);

      std::cout << "<!-- " << from_symbol << " " << to_symbol << " " << price
                << " " << name << " -->\n";

      // Only store non-zero prices
      if (price > 0.0)
        stage1_prices.push_back({price, name});
    }

    // Sort the prices before calculating the combinations
    std::sort(stage1_prices.begin(), stage1_prices.end());
    std::reverse(stage1_prices.begin(), stage1_prices.end());

    // Calculate average over all exchanges
    const auto average =
        (stage1_prices.empty()
             ? 0.0
             : std::accumulate(
                   stage1_prices.cbegin(), stage1_prices.cend(), 0.0,
                   [](double sum, const auto &p) { return sum += p.first; }) /
                   stage1_prices.size());

    // Print the combined prices
    if (!stage1_prices.empty()) {
      std::cout << std::fixed << std::setprecision(0);
      std::cout << "# " << from_symbol << "-" << to_symbol << " " << average
                << '\n';
      std::cout << "```\n";
      for (const auto &p : stage1_prices)
        std::cout << p.first << '\t' << p.second << '\n';
      std::cout << "```\n";
    }
  }
}
