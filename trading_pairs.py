#!/usr/bin/python3

import json
import requests

try:

    from_symbol = "BTC"
    to_symbol = "USD"

    good_exchanges = {}

    # Get all pairs from all exchanges
    url = "https://min-api.cryptocompare.com/data/all/exchanges"
    r = requests.get(url)
    exchanges = r.json();

    for name in exchanges:
        print(name)
        for from_symbol in exchanges[name]:
            print("  " + from_symbol)
            for to_symbol in exchanges[name][from_symbol]:
                print("    " + to_symbol)

except Exception as e:
    print("exception ", e)
