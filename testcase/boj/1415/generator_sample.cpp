#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    vector<int> prices;

    if (mode == 0) {
        n = rnd.next(1, 12);
        int distinct = rnd.next(1, min(4, n));
        vector<int> pool;
        for (int i = 0; i < distinct; ++i) pool.push_back(rnd.next(0, 12));
        for (int i = 0; i < n; ++i) prices.push_back(rnd.any(pool));
    } else if (mode == 1) {
        n = rnd.next(2, 15);
        int zeroCount = rnd.next(1, n);
        prices.assign(zeroCount, 0);
        while ((int)prices.size() < n) prices.push_back(rnd.next(1, 30));
    } else if (mode == 2) {
        n = rnd.next(3, 14);
        for (int i = 0; i < n; ++i) prices.push_back(2 * rnd.next(1, 100));
    } else if (mode == 3) {
        n = rnd.next(4, 16);
        int value = rnd.next(1, 3);
        for (int i = 0; i < n; ++i) {
            prices.push_back(value);
            if (rnd.next(0, 2) == 0 && value <= 5000) value *= 2;
        }
    } else if (mode == 4) {
        n = rnd.next(8, 25);
        for (int i = 0; i < n; ++i) prices.push_back(rnd.next(0, 10000));
    } else {
        n = rnd.next(35, 50);
        int base = rnd.next(0, 10000);
        for (int i = 0; i < n; ++i) {
            int delta = rnd.next(-20, 20);
            prices.push_back(max(0, min(10000, base + delta)));
        }
    }

    shuffle(prices.begin(), prices.end());

    println(n);
    for (int price : prices) println(price);

    return 0;
}
