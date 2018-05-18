#!/usr/bin/python3

import json
import requests

try:

    from_symbol = "ETH"
    to_symbol = "USD"

    good_exchanges = {}

    # Get all pairs from all exchanges
    url = 'https://min-api.cryptocompare.com/data/all/exchanges'
    r = requests.get(url)
    exchanges = r.json();

    print("Searching for " + from_symbol + "-" + to_symbol
            + " over " + str(len(exchanges)) + " exchanges")

    # for name in exchanges:
    #     if from_symbol in exchanges[name]:
    #         if to_symbol in exchanges[name][from_symbol]:
    #             url = ("https://min-api.cryptocompare.com/data/price?"
    #                 + "fsym=" + from_symbol
    #                 + "&tsyms=" + to_symbol
    #                 + "&e=" + name)

    #             r = requests.get(url)
    #             price = r.json();
    #             if price:
    #                 good_exchanges[name] = price[to_symbol]
    #                 # print(name, price[to_symbol])
    #                 print("\"" + name + "\",")

    for from_symbol in exchanges["Binance"]:
        for to_symbol in exchanges["Binance"][from_symbol]:
            print(from_symbol, "\t", to_symbol)

    print(len(good_exchanges), "good exchanges")
    # for name in sorted(good_exchanges, key=lambda x : good_exchanges[x]):
    #for name in good_exchanges:
        #print(name, good_exchanges[name])

except Exception as e:
    print("exception ", e)
