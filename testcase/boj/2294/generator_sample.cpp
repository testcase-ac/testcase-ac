#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

static vector<int> randomCoins(int n, int lo, int hi) {
    vector<int> coins;
    coins.reserve(n);
    for (int i = 0; i < n; ++i) {
        coins.push_back(rnd.next(lo, hi));
    }
    return coins;
}

static void printCase(int k, vector<int> coins) {
    shuffle(coins.begin(), coins.end());
    println((int)coins.size(), k);
    for (int coin : coins) {
        println(coin);
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int k;
    vector<int> coins;

    if (mode == 0) {
        int n = rnd.next(1, 12);
        k = rnd.next(1, 80);
        coins = randomCoins(n, 1, min(120, max(1, k * 2)));
    } else if (mode == 1) {
        int distinct = rnd.next(1, 5);
        int n = rnd.next(distinct, 18);
        k = rnd.next(20, 300);
        vector<int> base = randomCoins(distinct, 1, min(500, k + 80));
        coins.reserve(n);
        for (int i = 0; i < n; ++i) {
            coins.push_back(rnd.any(base));
        }
    } else if (mode == 2) {
        int n = rnd.next(2, 16);
        int step = rnd.next(2, 20);
        k = step * rnd.next(1, 120) + rnd.next(1, step - 1);
        coins.reserve(n);
        for (int i = 0; i < n; ++i) {
            coins.push_back(step * rnd.next(1, 80));
        }
    } else if (mode == 3) {
        int n = rnd.next(4, 20);
        k = rnd.next(1, 500);
        coins.reserve(n);
        coins.push_back(k);
        coins.push_back(max(1, k - rnd.next(0, min(k - 1, 20))));
        while ((int)coins.size() < n) {
            coins.push_back(rnd.next(k + 1, 100000));
        }
    } else if (mode == 4) {
        int n = rnd.next(20, 60);
        k = rnd.next(8000, 10000);
        coins = randomCoins(n, 1, 100000);
        coins[rnd.next(n)] = 1;
        coins[rnd.next(n)] = rnd.next(2, 100);
    } else {
        int n = rnd.next(8, 30);
        k = rnd.next(200, 2000);
        int base = rnd.next(2, 40);
        coins.reserve(n);
        coins.push_back(base);
        coins.push_back(base + 1);
        for (int i = 2; i < n; ++i) {
            coins.push_back(rnd.next(1, 4) * base + rnd.next(0, 3));
        }
    }

    printCase(k, coins);
    return 0;
}
