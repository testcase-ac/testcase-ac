#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

vector<int> makePrices(int n, int mode) {
    vector<int> prices;
    prices.reserve(n);

    if (mode == 0) {
        int value = rnd.next(1, 100) * 100;
        prices.assign(n, value);
    } else if (mode == 1) {
        for (int i = 0; i < n; ++i) {
            prices.push_back(rnd.next(1, 10) * 100);
        }
    } else if (mode == 2) {
        for (int i = 0; i < n; ++i) {
            prices.push_back(rnd.next(90, 100) * 100);
        }
    } else {
        for (int i = 0; i < n; ++i) {
            if (rnd.next(2) == 0) {
                prices.push_back(rnd.next(1, 5) * 100);
            } else {
                prices.push_back(rnd.next(80, 100) * 100);
            }
        }
    }

    shuffle(prices.begin(), prices.end());
    return prices;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(4);
    int b, c, d;
    if (mode == 0) {
        int base = rnd.next(1, 12);
        b = base;
        c = base;
        d = base;
    } else if (mode == 1) {
        int sets = rnd.next(1, 8);
        b = sets + rnd.next(0, 12);
        c = sets + rnd.next(0, 12);
        d = sets;
    } else if (mode == 2) {
        b = rnd.next(1, 5);
        c = rnd.next(10, 25);
        d = rnd.next(10, 25);
    } else {
        b = rnd.next(8, 25);
        c = rnd.next(1, 25);
        d = rnd.next(1, 25);
    }

    int priceMode = rnd.next(4);
    vector<int> burgers = makePrices(b, priceMode);
    vector<int> sides = makePrices(c, (priceMode + rnd.next(4)) % 4);
    vector<int> drinks = makePrices(d, (priceMode + rnd.next(4)) % 4);

    println(b, c, d);
    println(burgers);
    println(sides);
    println(drinks);

    return 0;
}
