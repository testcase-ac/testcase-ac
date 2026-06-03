#include "testlib.h"

#include <algorithm>
#include <set>
#include <vector>

using namespace std;

vector<int> randomDistinctPrices(int lo = 1, int hi = 250) {
    vector<int> pool;
    for (int x = lo; x <= hi; ++x) {
        pool.push_back(x);
    }
    shuffle(pool.begin(), pool.end());
    pool.resize(12);
    return pool;
}

vector<int> monotonePrices(bool increasing) {
    int start = rnd.next(1, 180);
    int step = rnd.next(1, 5);
    vector<int> prices(12);
    for (int i = 0; i < 12; ++i) {
        prices[i] = start + i * step;
    }
    if (!increasing) {
        reverse(prices.begin(), prices.end());
    }
    return prices;
}

vector<int> valleySpikePrices() {
    vector<int> prices = randomDistinctPrices(20, 230);
    int buyMonth = rnd.next(0, 10);
    int sellMonth = rnd.next(buyMonth + 1, 11);
    prices[buyMonth] = rnd.next(1, 9);
    prices[sellMonth] = rnd.next(231, 250);

    set<int> used;
    used.insert(prices[buyMonth]);
    used.insert(prices[sellMonth]);
    for (int i = 0; i < 12; ++i) {
        if (i == buyMonth || i == sellMonth) {
            continue;
        }
        while (!used.insert(prices[i]).second) {
            prices[i] = rnd.next(10, 230);
        }
    }
    return prices;
}

vector<int> lowPriceTiePrices() {
    vector<int> prices = randomDistinctPrices(30, 220);
    int lowA = rnd.next(1, 20);
    int lowB = rnd.next(lowA + 1, 30);
    int highA = lowA + rnd.next(30, 90);
    int highB = lowB + rnd.next(30, 90);

    set<int> used;
    vector<int> crafted = {lowB, highB, lowA, highA};
    for (int i = 0; i < 4; ++i) {
        while (!used.insert(crafted[i]).second) {
            crafted[i] = rnd.next(1, 120);
        }
        prices[i] = crafted[i];
    }
    for (int i = 4; i < 12; ++i) {
        while (!used.insert(prices[i]).second) {
            prices[i] = rnd.next(31, 220);
        }
    }
    return prices;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(3, 8);
    println(n);

    for (int tc = 0; tc < n; ++tc) {
        int mode = rnd.next(0, 5);
        int money = rnd.next(100, 500);
        vector<int> prices;

        if (mode == 0) {
            prices = monotonePrices(true);
        } else if (mode == 1) {
            prices = monotonePrices(false);
        } else if (mode == 2) {
            prices = valleySpikePrices();
        } else if (mode == 3) {
            prices = lowPriceTiePrices();
            money = rnd.next(120, 500);
        } else if (mode == 4) {
            prices = randomDistinctPrices(101, 250);
            money = rnd.next(100, 150);
        } else {
            prices = randomDistinctPrices();
        }

        if (rnd.next(0, 3) == 0) {
            shuffle(prices.begin(), prices.end());
        }

        println(money);
        println(prices);
    }

    return 0;
}
