#!/usr/bin/python3

import json
import requests

try:

    # Get all pairs from all exchanges
    url = 'https://min-api.cryptocompare.com/data/all/exchanges'
    r = requests.get(url)
    exchanges = r.json();

    for name in exchanges:
      for from_symbol in exchanges[name]:
         for to_symbol in exchanges[name][from_symbol]:
           print (name + "\t" + from_symbol + "\t" + to_symbol)

except Exception as e:
    print("exception ", e)
