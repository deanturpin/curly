#!/usr/bin/python3

import json
import requests

try:

    # Get all pairs from all exchanges
    url = ("https://min-api.cryptocompare.com/data/all/exchanges"
            "?extraParams=https://github.com/deanturpin/arbitrage")
    r = requests.get(url)
    exchanges = r.json();

    # Print all currency pairs
    for name in exchanges:
        for from_symbol in exchanges[name]:
            for to_symbol in exchanges[name][from_symbol]:
                print(name, from_symbol, to_symbol)

except Exception as e:
    print("exception ", e)
