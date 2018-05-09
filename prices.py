#!/usr/bin/python3

import json
import requests

try:

    # Get all pairs from all exchanges
    url = ("https://min-api.cryptocompare.com/data/all/exchanges"
            "?extraParams=https://github.com/deanturpin/arbitrage")
    r = requests.get(url)
    exchanges = r.json();

    # Header
    print(
        "#ifndef PRICES_H\n" +
        "#define PRICES_H\n" +
        "struct exchange {\n" +
        "  struct from_symbol{\n" +
        "    std::string name;\n" +
        "    std::vector<std::pair<std::string, double>> to_symbols;\n" +
        "  };\n" +
        "  std::string name;\n" +
        "  std::vector<from_symbol> symbols;\n" +
        "};\n" +
        "\n" +
        "const std::vector<exchange> exchanges {"
        )

    # Print all currency pairs
    for name in exchanges:

        if name == "EtherDelta":
            continue

        print("  {\"" + name + "\",{\n")

        for from_symbol in exchanges[name]:

        # if from_symbol == "BTC":
            print("    {\"" + from_symbol + "\", {", end=" ")

            for to_symbol in exchanges[name][from_symbol]:
                print("{\"" + to_symbol + "\", 0.0},", end=" ")

            print(" },},")
            # break

        print("  },")
        print("  },")

    # Footer
    print("};\n")
    print("#endif")

except Exception as e:
    print("exception ", e)
