[![Build
Status](https://travis-ci.org/deanturpin/arbitrage.svg?branch=master)](https://travis-ci.org/deanturpin/arbitrage)

All prices are fetched via the [CryptoCompare
API](https://min-api.cryptocompare.com/).

# Build and run
```bash
make update markets 
```

Written to avoid having to do the network bits in Python. Could be done with
```popen``` but it's quite useful to log all the messages.

# References
* https://en.wikipedia.org/wiki/Arbitrage
* https://en.wikipedia.org/wiki/Law_of_one_price
* https://en.wikipedia.org/wiki/Men%27s_underwear_index
