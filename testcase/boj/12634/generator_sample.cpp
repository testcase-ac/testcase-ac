#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

using Stock = vector<int>;

const int PRICE_MAX = 1000000;

Stock makeIncreasing(int k, int start, int stepMin, int stepMax) {
    Stock stock(k);
    int value = start;
    for (int j = 0; j < k; ++j) {
        stock[j] = min(value, PRICE_MAX);
        value += rnd.next(stepMin, stepMax);
    }
    return stock;
}

Stock makeZigzag(int k, int low, int high) {
    Stock stock(k);
    for (int j = 0; j < k; ++j) {
        if (j % 2 == 0) {
            stock[j] = rnd.next(low, (low + high) / 2);
        } else {
            stock[j] = rnd.next((low + high + 1) / 2, high);
        }
    }
    return stock;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int T = rnd.next(3, 8);
    println(T);

    for (int tc = 0; tc < T; ++tc) {
        int mode = rnd.next(5);
        int n = rnd.next(1, 10);
        int k = rnd.next(2, 8);
        vector<Stock> stocks;

        if (mode == 0) {
            // Strictly separated monotone stocks: many charts can be overlaid.
            n = rnd.next(2, 9);
            k = rnd.next(2, 7);
            int gap = rnd.next(5, 30);
            for (int i = 0; i < n; ++i) {
                stocks.push_back(makeIncreasing(k, i * gap + rnd.next(0, 3), 1, 8));
            }
        } else if (mode == 1) {
            // Equal or nearly equal rows force lines to touch.
            n = rnd.next(2, 10);
            k = rnd.next(2, 8);
            Stock base(k);
            for (int j = 0; j < k; ++j) {
                base[j] = rnd.next(0, 30);
            }
            for (int i = 0; i < n; ++i) {
                Stock stock = base;
                if (rnd.next(3) == 0) {
                    stock[rnd.next(k)] = rnd.next(0, 30);
                }
                stocks.push_back(stock);
            }
        } else if (mode == 2) {
            // Zigzags and shuffled time profiles create many crossings.
            n = rnd.next(2, 9);
            k = rnd.next(3, 8);
            for (int i = 0; i < n; ++i) {
                Stock stock = makeZigzag(k, rnd.next(0, 20), rnd.next(40, 90));
                if (rnd.next(2) == 0) {
                    reverse(stock.begin(), stock.end());
                }
                stocks.push_back(stock);
            }
        } else if (mode == 3) {
            // Several comparable clusters mixed with incomparable rows.
            n = rnd.next(4, 10);
            k = rnd.next(2, 8);
            int clusters = rnd.next(2, 4);
            for (int i = 0; i < n; ++i) {
                int c = i % clusters;
                Stock stock(k);
                for (int j = 0; j < k; ++j) {
                    int base = c * 80 + j * rnd.next(1, 7);
                    stock[j] = base + rnd.next(0, 25);
                }
                if (rnd.next(4) == 0) {
                    stock[rnd.next(k)] = rnd.next(0, 20);
                }
                stocks.push_back(stock);
            }
            shuffle(stocks.begin(), stocks.end());
        } else {
            // Boundary prices and short timelines.
            n = rnd.next(1, 8);
            k = rnd.next(2, 5);
            for (int i = 0; i < n; ++i) {
                Stock stock(k);
                for (int j = 0; j < k; ++j) {
                    int pick = rnd.next(5);
                    if (pick == 0) {
                        stock[j] = 0;
                    } else if (pick == 1) {
                        stock[j] = PRICE_MAX;
                    } else {
                        stock[j] = rnd.next(0, 100);
                    }
                }
                stocks.push_back(stock);
            }
        }

        println(static_cast<int>(stocks.size()), k);
        for (const Stock& stock : stocks) {
            println(stock);
        }
    }

    return 0;
}
