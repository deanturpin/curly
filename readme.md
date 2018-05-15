[![Build Status](https://travis-ci.org/deanturpin/curly.svg?branch=master)](https://travis-ci.org/deanturpin/curly)
[![codecov](https://codecov.io/gh/deanturpin/curly/branch/master/graph/badge.svg)](https://codecov.io/gh/deanturpin/curly)

Experimental header-only library providing minimal network connectivity and JSON
handling in C++ thereby removing the common dependency on Python. The library
essentially implements ```popen()``` and uses the installed ```curl``` binary
via ```system()```.

Prices are fetched via the [CryptoCompare API](https://min-api.cryptocompare.com/).

```
116 %   Bitlish 8310 > TrustDEX 9640
108 %   BitBay 8522 > Gatecoin 9184
107 %   Coinroom 8572 > BitFlip 9179
105 %   BTCChina 8684 > Yobit 9103
104 %   Exmo 8693 > LiveCoin 9065
104 %   DSX 8700 > ExtStock 9037
102 %   Coincap 8723 > LakeBTC 8900
102 %   Coinfloor 8726 > Lykke 8887
101 %   Quoine 8746 > Cexio 8826
101 %   Poloniex 8746 > QuadrigaCX 8802
100 %   Bitfinex 8751 > BitSquare 8783
100 %   Kraken 8751 > bitFlyer 8779
100 %   Gemini 8758 > HitBTC 8777
100 %   Coinbase 8758 > WavesDEX 8765
100 %   itBit 8761 > BitTrex 8764
100 %   Bitstamp 8762 > Bitstamp 8762
100 %   BitTrex 8764 > itBit 8761
100 %   WavesDEX 8765 > Coinbase 8758
100 %   HitBTC 8777 > Gemini 8758
100 %   bitFlyer 8779 > Kraken 8751
100 %   BitSquare 8783 > Bitfinex 8751
99 %    QuadrigaCX 8802 > Poloniex 8746
99 %    Cexio 8826 > Quoine 8746
98 %    Lykke 8887 > Coinfloor 8726
98 %    LakeBTC 8900 > Coincap 8723
96 %    ExtStock 9037 > DSX 8700
96 %    LiveCoin 9065 > Exmo 8693
95 %    Yobit 9103 > BTCChina 8684
93 %    BitFlip 9179 > Coinroom 8572
93 %    Gatecoin 9184 > BitBay 8522
86 %    TrustDEX 9640 > Bitlish 8310

```

# References
* https://en.wikipedia.org/wiki/Arbitrage
* https://en.wikipedia.org/wiki/Law_of_one_price
* https://en.wikipedia.org/wiki/Men%27s_underwear_index
