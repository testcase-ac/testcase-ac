#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    vector<pair<int, int>> apps;
    int M = 1;

    auto addApp = [&](int memory, int cost) {
        apps.push_back({memory, cost});
    };

    if (mode == 0) {
        int N = rnd.next(1, 12);
        for (int i = 0; i < N; ++i) {
            addApp(rnd.next(1, 200), rnd.next(0, 20));
        }
    } else if (mode == 1) {
        int N = rnd.next(6, 18);
        int freeMemory = 0;
        for (int i = 0; i < N; ++i) {
            int memory = rnd.next(1, 120);
            int cost = (i < N / 3 || rnd.next(0, 4) == 0) ? 0 : rnd.next(1, 30);
            freeMemory += cost == 0 ? memory : 0;
            addApp(memory, cost);
        }
        M = max(1, freeMemory + rnd.next(-min(freeMemory - 1, 20), 40));
    } else if (mode == 2) {
        int N = rnd.next(5, 16);
        int subsetSum = 0;
        for (int i = 0; i < N; ++i) {
            int memory = rnd.next(5, 80);
            int cost = i % 2 == 0 ? rnd.next(1, 8) : rnd.next(20, 80);
            if (i % 2 == 0) subsetSum += memory;
            addApp(memory, cost);
        }
        M = subsetSum;
    } else if (mode == 3) {
        int N = rnd.next(8, 30);
        int base = rnd.next(100000, 600000);
        for (int i = 0; i < N; ++i) {
            int memory = min(10000000, base + rnd.next(0, base));
            int cost = rnd.next(0, 100);
            addApp(memory, cost);
        }
    } else if (mode == 4) {
        int N = rnd.next(10, 25);
        for (int i = 0; i < N; ++i) {
            int memory = i % 4 == 0 ? rnd.next(300, 1000) : rnd.next(1, 100);
            int cost = rnd.any(vector<int>{0, 1, 2, 99, 100});
            addApp(memory, cost);
        }
    } else {
        int N = rnd.next(20, 60);
        for (int i = 0; i < N; ++i) {
            int memory = rnd.next(1, 500);
            int cost = rnd.next(0, 100);
            addApp(memory, cost);
        }
    }

    long long totalMemory = 0;
    for (auto [memory, cost] : apps) {
        totalMemory += memory;
    }
    if (mode != 1 && mode != 2) {
        M = rnd.next(1, (int)min<long long>(10000000, totalMemory));
    }
    M = min<long long>(M, totalMemory);

    shuffle(apps.begin(), apps.end());

    vector<int> memories;
    vector<int> costs;
    for (auto [memory, cost] : apps) {
        memories.push_back(memory);
        costs.push_back(cost);
    }

    println((int)apps.size(), M);
    println(memories);
    println(costs);

    return 0;
}
