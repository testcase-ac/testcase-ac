#include "testlib.h"

#include <algorithm>
#include <set>
#include <vector>

using namespace std;

static vector<int> uniqueCoins(int count, int maxCoin) {
    set<int> seen;
    while ((int)seen.size() < count) {
        seen.insert(rnd.next(1, maxCoin));
    }
    return vector<int>(seen.begin(), seen.end());
}

static void printCase(int target, vector<int> coins) {
    shuffle(coins.begin(), coins.end());
    println((int)coins.size(), target);
    for (int coin : coins) {
        println(coin);
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int target;
    vector<int> coins;

    if (mode == 0) {
        target = rnd.next(1, 20);
        coins = uniqueCoins(rnd.next(1, 6), 25);
    } else if (mode == 1) {
        target = rnd.next(1, 60);
        coins = {1};
        int extra = rnd.next(0, 7);
        while ((int)coins.size() < extra + 1) {
            int candidate = rnd.next(2, 40);
            if (find(coins.begin(), coins.end(), candidate) == coins.end()) {
                coins.push_back(candidate);
            }
        }
    } else if (mode == 2) {
        target = rnd.next(30, 200);
        coins = {1, 2, 5, 10, 20, 50, 100};
        int keep = rnd.next(2, (int)coins.size());
        shuffle(coins.begin(), coins.end());
        coins.resize(keep);
    } else if (mode == 3) {
        target = rnd.next(1, 200);
        int count = rnd.next(1, 8);
        coins = uniqueCoins(count, 250);
        for (int& coin : coins) {
            if (rnd.next(0, 2) == 0) {
                coin += target;
            }
        }
    } else if (mode == 4) {
        target = rnd.next(500, 10000);
        int count = rnd.next(1, 10);
        coins = uniqueCoins(count, 10000);
        for (int& coin : coins) {
            coin = max(coin, rnd.next(200, 10000));
        }
        sort(coins.begin(), coins.end());
        coins.erase(unique(coins.begin(), coins.end()), coins.end());
    } else {
        target = rnd.next(1, 120);
        int count = rnd.next(10, 25);
        coins = uniqueCoins(count, 300);
    }

    printCase(target, coins);
    return 0;
}
