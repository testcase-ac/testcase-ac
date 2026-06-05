#include "testlib.h"
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, mode == 5 ? 40 : 18);
    vector<pair<int, int>> tasks;
    tasks.reserve(n);

    if (mode == 0) {
        int base = rnd.next(1, 8);
        for (int i = 0; i < n; ++i) {
            int d = min(100000, base + rnd.next(0, 12));
            int t = rnd.next(1, 5);
            tasks.emplace_back(d, t);
        }
    } else if (mode == 1) {
        int d = rnd.next(1, 20);
        for (int i = 0; i < n; ++i) {
            int drift = rnd.next(0, 2);
            int t = rnd.next(1, 9);
            tasks.emplace_back(min(100000, d + drift), t);
        }
    } else if (mode == 2) {
        int d = rnd.next(1, 6);
        for (int i = 0; i < n; ++i) {
            d += rnd.next(0, 7);
            int t = rnd.next(1, 4);
            if (rnd.next(0, 4) == 0) t = rnd.next(8, 25);
            tasks.emplace_back(min(100000, d), t);
        }
    } else if (mode == 3) {
        for (int i = 0; i < n; ++i) {
            int d = rnd.next(1, 30);
            int t = rnd.next(1, 30);
            tasks.emplace_back(d, t);
        }
    } else if (mode == 4) {
        int nearMax = rnd.next(99970, 100000);
        for (int i = 0; i < n; ++i) {
            int d = rnd.next(1, 4) == 1 ? nearMax : rnd.next(1, 100);
            int t = rnd.next(1, 4) == 1 ? rnd.next(99970, 100000) : rnd.next(1, 20);
            tasks.emplace_back(d, t);
        }
    } else {
        int d = rnd.next(1, 12);
        for (int i = 0; i < n; ++i) {
            d += rnd.next(0, 4);
            int t = rnd.wnext(12, -2) + 1;
            tasks.emplace_back(min(100000, d), t);
        }
    }

    shuffle(tasks.begin(), tasks.end());

    println(n);
    for (auto [d, t] : tasks) {
        println(d, t);
    }

    return 0;
}
