#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = rnd.next(1, 12);
    int k = rnd.next(1, 12);

    vector<pair<int, int>> jewels;
    vector<int> bags;
    jewels.reserve(n);
    bags.reserve(k);

    if (mode == 0) {
        int maxWeight = rnd.next(1, 20);
        int maxValue = rnd.next(0, 40);
        int maxCapacity = rnd.next(1, 25);
        for (int i = 0; i < n; ++i) {
            jewels.push_back({rnd.next(0, maxWeight), rnd.next(0, maxValue)});
        }
        for (int i = 0; i < k; ++i) {
            bags.push_back(rnd.next(1, maxCapacity));
        }
    } else if (mode == 1) {
        int base = rnd.next(1, 8);
        for (int i = 0; i < n; ++i) {
            int weight = max(0, base + rnd.next(-2, 3));
            int value = rnd.next(0, 60);
            jewels.push_back({weight, value});
        }
        for (int i = 0; i < k; ++i) {
            bags.push_back(max(1, base + rnd.next(-3, 3)));
        }
    } else if (mode == 2) {
        int heavy = rnd.next(10, 30);
        for (int i = 0; i < n; ++i) {
            int weight = (i % 3 == 0) ? rnd.next(0, 2) : rnd.next(heavy - 4, heavy + 4);
            int value = (i % 3 == 0) ? rnd.next(0, 25) : rnd.next(25, 80);
            jewels.push_back({max(0, weight), value});
        }
        for (int i = 0; i < k; ++i) {
            bags.push_back((i % 2 == 0) ? rnd.next(1, 3) : rnd.next(heavy - 2, heavy + 5));
        }
    } else if (mode == 3) {
        int sharedWeight = rnd.next(0, 10);
        int sharedCapacity = max(1, sharedWeight + rnd.next(0, 3));
        for (int i = 0; i < n; ++i) {
            jewels.push_back({sharedWeight, rnd.next(0, 100)});
        }
        for (int i = 0; i < k; ++i) {
            bags.push_back(sharedCapacity);
        }
    } else {
        n = rnd.next(6, 16);
        k = rnd.next(3, 10);
        for (int i = 0; i < n; ++i) {
            int weight = (i % 2 == 0) ? i / 2 : rnd.next(0, 12);
            int value = 100 - i * rnd.next(1, 5);
            jewels.push_back({weight, max(0, value)});
        }
        for (int i = 0; i < k; ++i) {
            bags.push_back(rnd.next(1, 12));
        }
    }

    shuffle(jewels.begin(), jewels.end());
    shuffle(bags.begin(), bags.end());

    println(n, k);
    for (const auto& jewel : jewels) {
        println(jewel.first, jewel.second);
    }
    for (int capacity : bags) {
        println(capacity);
    }

    return 0;
}
