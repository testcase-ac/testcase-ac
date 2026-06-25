#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

struct Coin {
    int value;
    int count;
};

vector<int> distinctValues(int n, int lo, int hi) {
    set<int> used;
    while ((int)used.size() < n) {
        used.insert(rnd.next(lo, hi));
    }

    vector<int> values(used.begin(), used.end());
    shuffle(values.begin(), values.end());
    return values;
}

vector<Coin> makeCase(int& target) {
    int mode = rnd.next(0, 5);
    int n;
    vector<int> values;
    vector<Coin> coins;

    if (mode == 0) {
        target = rnd.next(1, 30);
        coins.push_back({rnd.next(1, 30), rnd.next(1, 20)});
    } else if (mode == 1) {
        n = rnd.next(2, 8);
        values = distinctValues(n, 1, 25);
        int perValue = rnd.next(1, 8);
        int chosen = rnd.next(1, n);
        target = 0;
        for (int i = 0; i < chosen; ++i) {
            target += values[i] * perValue;
        }
        for (int value : values) {
            coins.push_back({value, rnd.next(perValue, 20)});
        }
    } else if (mode == 2) {
        n = rnd.next(2, 10);
        values = distinctValues(n, 20, 80);
        target = rnd.next(1, 19);
        for (int value : values) {
            coins.push_back({value, rnd.next(1, 15)});
        }
    } else if (mode == 3) {
        n = rnd.next(3, 12);
        values = distinctValues(n, 1, 40);
        target = rnd.next(1, 200);
        for (int value : values) {
            coins.push_back({value, rnd.next(1, 4)});
        }
    } else if (mode == 4) {
        n = rnd.next(2, 8);
        values = distinctValues(n, 1, 5000);
        target = 5000;
        for (int value : values) {
            coins.push_back({value, rnd.next(1, 5000)});
        }
    } else {
        n = rnd.next(8, 18);
        values = distinctValues(n, 1, 120);
        target = rnd.next(200, 1200);
        for (int value : values) {
            coins.push_back({value, rnd.next(5, 60)});
        }
    }

    shuffle(coins.begin(), coins.end());
    return coins;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 8);
    println(t);
    for (int tc = 0; tc < t; ++tc) {
        int target;
        vector<Coin> coins = makeCase(target);

        println(target, (int)coins.size());
        for (const Coin& coin : coins) {
            println(coin.value, coin.count);
        }
    }

    return 0;
}
