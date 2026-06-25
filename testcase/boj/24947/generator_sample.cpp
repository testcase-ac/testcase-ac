#include "testlib.h"

#include <algorithm>
#include <array>
#include <vector>

using namespace std;

using Beaver = array<int, 3>;

const int LIM = 100000000;

int bounded(int value) {
    return max(1, min(LIM, value));
}

void addJitter(vector<Beaver>& beavers, int amount) {
    for (auto& b : beavers) {
        for (int& v : b) {
            v = bounded(v + rnd.next(-amount, amount));
        }
    }
}

void printCase(vector<Beaver> beavers) {
    shuffle(beavers.begin(), beavers.end());
    println((int)beavers.size());
    for (const auto& b : beavers) {
        println(b[0], b[1], b[2]);
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(6);
    vector<Beaver> beavers;

    if (mode == 0) {
        int n = rnd.next(3, 12);
        int x = rnd.next(1, 20);
        int y = rnd.next(1, 20);
        int z = rnd.next(1, 20);
        beavers.assign(n, {x, y, z});
    } else if (mode == 1) {
        int high = rnd.next(30, 200);
        int low = rnd.next(1, high - 2);
        beavers = {
            {high, low, low},
            {low, high, low},
            {low, low, high},
        };
        int extras = rnd.next(0, 6);
        for (int i = 0; i < extras; ++i) {
            beavers.push_back({rnd.next(low, high - 1), rnd.next(low, high - 1), rnd.next(low, high - 1)});
        }
    } else if (mode == 2) {
        int n = rnd.next(3, 10);
        int base = rnd.next(1, 30);
        for (int i = 0; i < n; ++i) {
            beavers.push_back({base + i * 3, base + i * 3 + 1, base + i * 3 + 2});
        }
    } else if (mode == 3) {
        int n = rnd.next(4, 14);
        int a = rnd.next(1, 10);
        int b = rnd.next(11, 25);
        int c = rnd.next(26, 50);
        for (int i = 0; i < n; ++i) {
            Beaver cur = {rnd.any(vector<int>{a, b, c}), rnd.any(vector<int>{a, b, c}), rnd.any(vector<int>{a, b, c})};
            beavers.push_back(cur);
        }
    } else if (mode == 4) {
        int n = rnd.next(3, 18);
        int cap = rnd.any(vector<int>{5, 20, 300, 4000});
        for (int i = 0; i < n; ++i) {
            beavers.push_back({rnd.next(1, cap), rnd.next(1, cap), rnd.next(1, cap)});
        }
    } else {
        beavers = {
            {LIM, 1, 1},
            {1, LIM, 1},
            {1, 1, LIM},
        };
        int extras = rnd.next(0, 5);
        for (int i = 0; i < extras; ++i) {
            beavers.push_back({rnd.next(LIM - 10, LIM), rnd.next(1, 12), rnd.next(1, 12)});
        }
        addJitter(beavers, rnd.next(0, 3));
    }

    printCase(beavers);
    return 0;
}
