#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 25);
    vector<pair<long long, long long>> blocks;

    if (mode == 0) {
        long long center = rnd.next(5, 40);
        for (int i = 0; i < n; ++i) {
            long long w = rnd.next(1, 12);
            long long d = max(1LL, center - rnd.next(0, 8));
            blocks.push_back({w, d});
        }
    } else if (mode == 1) {
        long long d = rnd.next(1, 10);
        for (int i = 0; i < n; ++i) {
            long long w = rnd.next(1, 8);
            blocks.push_back({w, d});
            d += w + rnd.next(1, 5);
        }
    } else if (mode == 2) {
        long long base = rnd.next(1, 25);
        for (int i = 0; i < n; ++i) {
            long long w = rnd.next(1, 15);
            long long d = base + rnd.next(0, 6);
            blocks.push_back({w, d});
        }
    } else if (mode == 3) {
        long long right = rnd.next(15, 60);
        for (int i = 0; i < n; ++i) {
            long long w = rnd.next(1LL, min(20LL, right));
            long long d = right - w + 1;
            blocks.push_back({w, d});
        }
    } else if (mode == 4) {
        long long origin = 1000000000LL - rnd.next(0, 200);
        for (int i = 0; i < n; ++i) {
            long long w = rnd.next(1, 120);
            long long d = origin - rnd.next(0, 120);
            blocks.push_back({w, d});
        }
    } else {
        for (int i = 0; i < n; ++i) {
            long long w = rnd.next(1, 30);
            long long d = rnd.next(1, 60);
            blocks.push_back({w, d});
        }
    }

    if (rnd.next(0, 1) == 1) {
        shuffle(blocks.begin(), blocks.end());
    }

    println((int)blocks.size());
    for (auto [w, d] : blocks) {
        println(w, d);
    }

    return 0;
}
