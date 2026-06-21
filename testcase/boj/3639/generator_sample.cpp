#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

struct Jewel {
    int value;
    int weight;
};

int remainingBudget(const vector<Jewel>& jewels, bool valueBudget) {
    int used = 0;
    for (const Jewel& jewel : jewels) {
        used += valueBudget ? jewel.value : jewel.weight;
    }
    return 10000000 - used;
}

void addRandomJewels(vector<Jewel>& jewels, int targetN, int maxValue, int maxWeight) {
    while ((int)jewels.size() < targetN) {
        int valueLimit = min(maxValue, remainingBudget(jewels, true));
        int weightLimit = min(maxWeight, remainingBudget(jewels, false));
        int value = rnd.next(0, valueLimit);
        int weight = rnd.next(1, weightLimit);
        jewels.push_back({value, weight});
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<Jewel> jewels;
    int mode = rnd.next(0, 5);
    int n = 0;
    int k = 0;

    if (mode == 0) {
        n = rnd.next(1, 6);
        k = rnd.next(1, n);
        addRandomJewels(jewels, n, 30, 30);
    } else if (mode == 1) {
        n = rnd.next(4, 12);
        k = rnd.next(1, min(n, 4));
        jewels.push_back({0, rnd.next(1, 20)});
        jewels.push_back({1000000, 1});
        jewels.push_back({rnd.next(500000, 1000000), rnd.next(1, 5)});
        jewels.push_back({rnd.next(0, 20), rnd.next(500000, 1000000)});
        addRandomJewels(jewels, n, 1000000, 1000000);
    } else if (mode == 2) {
        n = rnd.next(5, 15);
        k = rnd.next(max(1, n - 4), n);
        int valueUnit = rnd.next(0, 20);
        int weightUnit = rnd.next(1, 20);
        for (int i = 0; i < n; ++i) {
            int scale = rnd.next(1, 6);
            jewels.push_back({valueUnit * scale, weightUnit * scale});
        }
    } else if (mode == 3) {
        n = rnd.next(8, 18);
        k = rnd.next(2, n - 1);
        int totalValue = 0;
        int totalWeight = 0;
        for (int i = 0; i < n; ++i) {
            int valueLimit = min(200000, 10000000 - totalValue);
            int weightLimit = min(200000, 10000000 - totalWeight);
            int value = (i % 3 == 0) ? 0 : rnd.next(0, valueLimit);
            int weight = rnd.next(1, weightLimit);
            jewels.push_back({value, weight});
            totalValue += value;
            totalWeight += weight;
        }
    } else {
        n = rnd.next(10, 25);
        k = rnd.next(1, n);
        for (int i = 0; i < n; ++i) {
            int base = rnd.next(1, 40);
            int value = min(1000000, base * rnd.next(0, 100));
            int weight = min(1000000, base * rnd.next(1, 100));
            jewels.push_back({value, weight});
        }
    }

    shuffle(jewels.begin(), jewels.end());

    println(n, k);
    for (const Jewel& jewel : jewels) {
        println(jewel.value, jewel.weight);
    }

    return 0;
}
