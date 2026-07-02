#include "testlib.h"
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long MAX_VALUE = 1000000000LL;

    int mode = rnd.next(0, 5);
    int h = 1;
    int c = 1;
    vector<pair<long long, long long>> coworkers;

    if (mode == 0) {
        h = rnd.next(1, 25);
        c = rnd.next(1, 12);
        long long maxA = rnd.next(1, 40);
        long long maxD = rnd.next(1, 40);
        for (int i = 0; i < c; ++i) {
            coworkers.push_back({rnd.next(1LL, maxA), rnd.next(1LL, maxD)});
        }
    } else if (mode == 1) {
        h = rnd.next(1, 100000);
        c = 1;
        long long a = rnd.next(MAX_VALUE - 1000, MAX_VALUE);
        long long d = rnd.next(MAX_VALUE - 1000, MAX_VALUE);
        coworkers.push_back({a, d});
    } else if (mode == 2) {
        h = rnd.next(1, 8);
        c = rnd.next(h + 1, 20);
        for (int i = 0; i < c; ++i) {
            long long a = rnd.next(1LL, 100LL);
            long long d = rnd.next(1LL, 1000LL);
            coworkers.push_back({a, d});
        }
    } else if (mode == 3) {
        h = rnd.next(10, 80);
        c = rnd.next(3, 15);
        long long base = rnd.next(1LL, 1000LL);
        for (int i = 0; i < c; ++i) {
            long long a = base + rnd.next(0LL, 3LL);
            long long d = rnd.next(1LL, 12LL);
            coworkers.push_back({a, d});
        }
    } else if (mode == 4) {
        h = rnd.next(20, 150);
        c = rnd.next(2, 12);
        long long smallD = rnd.next(1LL, 5LL);
        coworkers.push_back({rnd.next(1LL, 20LL), smallD});
        for (int i = 1; i < c; ++i) {
            long long a = rnd.next(1LL, 1000000LL);
            long long d = rnd.next(1000000LL, MAX_VALUE);
            coworkers.push_back({a, d});
        }
    } else {
        h = rnd.next(500, 5000);
        c = rnd.next(10, 30);
        long long anchor = rnd.next(MAX_VALUE - 100000, MAX_VALUE);
        for (int i = 0; i < c; ++i) {
            long long a = rnd.next(max(1LL, anchor - 1000), anchor);
            long long d = rnd.next(1LL, 1000000000LL);
            coworkers.push_back({a, d});
        }
    }

    shuffle(coworkers.begin(), coworkers.end());

    println(h, c);
    for (auto coworker : coworkers) {
        println(coworker.first, coworker.second);
    }

    return 0;
}
