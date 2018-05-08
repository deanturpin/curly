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
        "std::string name;\n" +
        "struct {\n" +
            "std::string name;\n" +
            "std::vector<std::pair<std::string, double>> to_symbols;\n" +
        "} from_symbol;\n" +
        "};\n\n" +
        "const std::vector<exchange> prices {"
        )

    # Print all currency pairs
    iteration = 0
    for name in exchanges:
        print("  {\"" + name + "\",")

        for from_symbol in exchanges[name]:
            print("    {\"" + from_symbol + "\", {", end=" ")

            for to_symbol in exchanges[name][from_symbol]:
                print("{\"" + to_symbol + "\", 0.0},", end=" ")

            print(" },}")

            iteration += 1
            if iteration > 5:
                break

        print("  },")


    # Footer
    print("};\n")
    print("#endif")

except Exception as e:
    print("exception ", e)
