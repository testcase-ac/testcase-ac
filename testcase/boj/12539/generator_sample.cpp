#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

vector<int> shuffledPrices(int low, int high) {
    vector<int> values;
    for (int x = low; x <= high; ++x) {
        values.push_back(x);
    }
    shuffle(values.begin(), values.end());
    values.resize(12);
    return values;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int cases = rnd.next(1, 10);
    println(cases);

    for (int tc = 0; tc < cases; ++tc) {
        int money = rnd.next(100, 500);
        int mode = rnd.next(6);
        vector<int> prices;

        if (mode == 0) {
            int start = rnd.next(1, 120);
            int step = rnd.next(1, max(1, (250 - start) / 11));
            for (int i = 0; i < 12; ++i) {
                prices.push_back(start + i * step);
            }
        } else if (mode == 1) {
            int start = rnd.next(12, 250);
            int step = rnd.next(1, max(1, (start - 1) / 11));
            for (int i = 0; i < 12; ++i) {
                prices.push_back(start - i * step);
            }
        } else if (mode == 2) {
            prices = shuffledPrices(21, 199);
            int buyMonth = rnd.next(0, 8);
            int sellMonth = rnd.next(buyMonth + 1, 11);
            prices[buyMonth] = rnd.next(1, 20);
            prices[sellMonth] = rnd.next(200, 250);
        } else if (mode == 3) {
            for (int i = 0; i < 6; ++i) {
                prices.push_back(1 + i);
                prices.push_back(250 - i);
            }
            shuffle(prices.begin(), prices.end());
        } else if (mode == 4) {
            int base = rnd.next(max(1, money / 2 - 15), min(239, money / 2 + 15));
            for (int i = 0; i < 12; ++i) {
                prices.push_back(base + i);
            }
            shuffle(prices.begin(), prices.end());
        } else {
            prices = shuffledPrices(1, 250);
        }

        println(money);
        println(prices);
    }

    return 0;
}
