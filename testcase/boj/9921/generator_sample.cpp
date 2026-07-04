#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 12);
    int targetValue = rnd.next(1, 150);
    int targetWeight = rnd.next(1, 150);
    vector<pair<int, int>> coins;

    auto addCoin = [&](int value, int weight) {
        value = max(1, min(150, value));
        weight = max(1, min(150, weight));
        pair<int, int> coin = {value, weight};
        if (find(coins.begin(), coins.end(), coin) == coins.end()) {
            coins.push_back(coin);
        }
    };

    if (mode == 0) {
        n = rnd.next(1, 8);
        int baseValue = rnd.next(1, 18);
        int baseWeight = rnd.next(1, 18);
        int multiplier = rnd.next(1, 6);
        targetValue = baseValue * multiplier;
        targetWeight = baseWeight * multiplier;
        addCoin(baseValue, baseWeight);
    } else if (mode == 1) {
        n = rnd.next(2, 10);
        int parts = rnd.next(2, min(5, n));
        targetValue = 0;
        targetWeight = 0;
        for (int i = 0; i < parts; ++i) {
            int value = rnd.next(1, 25);
            int weight = rnd.next(1, 25);
            int count = rnd.next(1, 3);
            addCoin(value, weight);
            targetValue += value * count;
            targetWeight += weight * count;
        }
        targetValue = min(targetValue, 150);
        targetWeight = min(targetWeight, 150);
    } else if (mode == 2) {
        n = rnd.next(2, 12);
        targetValue = rnd.next(1, 149);
        targetWeight = rnd.next(1, 149);
        int commonWeight = rnd.next(1, 20);
        for (int value = rnd.next(1, 8); (int)coins.size() < n && value <= 150; value += rnd.next(1, 9)) {
            addCoin(value, commonWeight);
        }
    } else if (mode == 3) {
        n = rnd.next(2, 12);
        targetValue = rnd.next(1, 149);
        targetWeight = rnd.next(1, 149);
        int commonValue = rnd.next(1, 20);
        for (int weight = rnd.next(1, 8); (int)coins.size() < n && weight <= 150; weight += rnd.next(1, 9)) {
            addCoin(commonValue, weight);
        }
    } else if (mode == 4) {
        n = rnd.next(4, 14);
        targetValue = rnd.next(120, 150);
        targetWeight = rnd.next(120, 150);
        for (int i = 0; i < n; ++i) {
            addCoin(rnd.next(90, 150), rnd.next(90, 150));
        }
    } else {
        n = rnd.next(8, 20);
        targetValue = rnd.next(1, 150);
        targetWeight = rnd.next(1, 150);
    }

    while ((int)coins.size() < n) {
        int value;
        int weight;
        if (mode <= 1 && rnd.next(0, 1) == 0) {
            value = rnd.next(1, max(1, targetValue));
            weight = rnd.next(1, max(1, targetWeight));
        } else {
            value = rnd.next(1, 150);
            weight = rnd.next(1, 150);
        }
        addCoin(value, weight);
    }

    shuffle(coins.begin(), coins.end());

    println((int)coins.size(), targetValue, targetWeight);
    for (auto coin : coins) {
        println(coin.first, coin.second);
    }

    return 0;
}
