#include "testlib.h"
#include <algorithm>
#include <climits>
#include <vector>
using namespace std;

struct TestCase {
    vector<int> coins;
    int target;
};

long long countWays(const vector<int>& coins, int target) {
    vector<long long> dp(target + 1);
    dp[0] = 1;
    for (int coin : coins) {
        for (int value = coin; value <= target; ++value) {
            dp[value] += dp[value - coin];
            if (dp[value] > INT_MAX) dp[value] = (long long)INT_MAX + 1;
        }
    }
    return dp[target];
}

vector<int> sortedUnique(vector<int> coins) {
    sort(coins.begin(), coins.end());
    coins.erase(unique(coins.begin(), coins.end()), coins.end());
    return coins;
}

TestCase makeSingletonCase() {
    int coin = rnd.next(1, 10000);
    int multiplier = rnd.next(1, max(1, 10000 / coin));
    int target = coin * multiplier;
    if (rnd.next(3) == 0) target = rnd.next(1, 10000);
    return {{coin}, target};
}

TestCase makeSparseCase() {
    int n = rnd.next(2, 8);
    vector<int> coins;
    while ((int)coins.size() < n) {
        coins.push_back(rnd.next(1, 10000));
        coins = sortedUnique(coins);
    }
    int target = rnd.next(1, 10000);
    return {coins, target};
}

TestCase makeDenominationCase() {
    vector<int> base = {1, 5, 10, 50, 100, 500, 1000, 5000, 10000};
    shuffle(base.begin(), base.end());
    int n = rnd.next(2, 6);
    vector<int> coins(base.begin(), base.begin() + n);
    coins = sortedUnique(coins);
    int target = rnd.next(1, 3000);
    return {coins, target};
}

TestCase makeNearTargetCase() {
    int target = rnd.next(20, 10000);
    vector<int> coins = {rnd.next(1, min(20, target))};
    int n = rnd.next(2, 7);
    while ((int)coins.size() < n) {
        int lo = max(1, target - rnd.next(0, 40));
        int hi = min(10000, target + rnd.next(0, 40));
        coins.push_back(rnd.next(lo, hi));
        coins = sortedUnique(coins);
    }
    return {coins, target};
}

TestCase makeMediumCase() {
    int n = rnd.next(10, 20);
    int start = rnd.next(1, 30);
    int step = rnd.next(2, 20);
    vector<int> coins;
    for (int i = 0; i < n; ++i) {
        int coin = start + i * step + rnd.next(0, step - 1);
        if (coin <= 10000) coins.push_back(coin);
    }
    coins = sortedUnique(coins);
    int target = rnd.next(100, 2000);
    return {coins, target};
}

TestCase makeCase() {
    for (int attempt = 0; attempt < 200; ++attempt) {
        TestCase tc;
        int mode = rnd.next(5);
        if (mode == 0) tc = makeSingletonCase();
        else if (mode == 1) tc = makeSparseCase();
        else if (mode == 2) tc = makeDenominationCase();
        else if (mode == 3) tc = makeNearTargetCase();
        else tc = makeMediumCase();

        if (!tc.coins.empty() && tc.coins.size() <= 20 &&
            1 <= tc.target && tc.target <= 10000 &&
            countWays(tc.coins, tc.target) < INT_MAX) {
            return tc;
        }
    }

    return {{1, 5, 10}, rnd.next(1, 200)};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(3, 8);
    println(t);
    for (int i = 0; i < t; ++i) {
        TestCase tc = makeCase();
        println((int)tc.coins.size());
        println(tc.coins);
        println(tc.target);
    }

    return 0;
}
