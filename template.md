[![Build Status](https://travis-ci.org/deanturpin/curly.svg?branch=master)](https://travis-ci.org/deanturpin/curly)
[![codecov](https://codecov.io/gh/deanturpin/curly/branch/master/graph/badge.svg)](https://codecov.io/gh/deanturpin/curly)

Exploring the price differential between crypto currency exchanges. Website
build, code coverage and deployment to GitHub pages managed in Travis CI.

Also an experimental header-only library providing minimal network connectivity
and JSON handling in C++ thereby removing the common dependency on Python. The
library essentially implements ```popen()``` and uses the installed ```curl```
binary via ```system()```.

The following info is generated periodically using prices from the
[CryptoCompare API](https://min-api.cryptocompare.com/). See
[references](references.md).

# ETH-USD 109 %
```
745	BitFlip
735	Yobit
719	ExtStock
718	LiveCoin
714	CCEX
714	Cexio
708	Exmo
707	Coinbase
707	HitBTC
707	Bitlish
706	BitTrex
706	Bitstamp
706	Gemini
705	Lykke
705	Bitfinex
705	Coincap
704	Kraken
704	Poloniex
700	DSX
700	Quoine
695	Gatecoin
691	Coinroom
690	BitBay
683	WavesDEX
```
Generated Wed 16 May 12:26:39 BST 2018
