#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 40);
    vector<pair<long long, long long>> dominoes;

    if (mode == 0) {
        long long x = rnd.next(1, 20);
        for (int i = 0; i < n; ++i) {
            long long gap = rnd.next(2, 8);
            x += gap;
            dominoes.push_back({x, rnd.next(1LL, gap - 1)});
        }
    } else if (mode == 1) {
        long long x = rnd.next(1, 15);
        for (int i = 0; i < n; ++i) {
            long long step = rnd.next(1, 5);
            dominoes.push_back({x, step});
            x += step;
        }
    } else if (mode == 2) {
        long long x = rnd.next(1, 30);
        for (int i = 0; i < n; ++i) {
            long long step = rnd.next(1, 7);
            long long length = step + rnd.next(0, 8);
            if (i > 0 && rnd.next(0, 4) == 0) {
                x += rnd.next(1, 4);
            }
            dominoes.push_back({x, length});
            x += step;
        }
    } else if (mode == 3) {
        int clusters = rnd.next(1, 5);
        long long x = rnd.next(1, 20);
        for (int c = 0; c < clusters && (int)dominoes.size() < n; ++c) {
            int size = rnd.next(1, min(10, n - (int)dominoes.size()));
            for (int i = 0; i < size; ++i) {
                long long step = rnd.next(1, 4);
                dominoes.push_back({x, rnd.next(step, step + 5)});
                x += step;
            }
            x += rnd.next(5, 20);
        }
    } else if (mode == 4) {
        long long x = 1000000000LL - rnd.next(200, 500);
        for (int i = 0; i < n; ++i) {
            long long step = rnd.next(1, 10);
            dominoes.push_back({x, rnd.next(1LL, 1000000000LL)});
            x += step;
        }
    } else {
        set<long long> used;
        while ((int)dominoes.size() < n) {
            long long x = rnd.next(1LL, 500LL);
            if (used.insert(x).second) {
                dominoes.push_back({x, rnd.next(1LL, 80LL)});
            }
        }
    }

    if (rnd.next(0, 1)) {
        shuffle(dominoes.begin(), dominoes.end());
    }

    println((int)dominoes.size());
    for (auto [x, length] : dominoes) {
        println(x, length);
    }

    return 0;
}
