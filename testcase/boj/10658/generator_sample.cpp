#include "testlib.h"

#include <algorithm>
#include <set>
#include <string>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long LIM = 1000000000LL;
    int mode = rnd.next(0, 4);
    vector<pair<string, long long>> cows;
    long long a = 1;
    long long b = 1;

    auto addCow = [&](const string& spotted, long long weight) {
        cows.push_back({spotted, weight});
    };

    if (mode == 0) {
        a = rnd.next(1LL, 20LL);
        b = rnd.next(a, min(LIM, a + rnd.next(0LL, 20LL)));
        long long w = rnd.next(1LL, LIM);
        addCow(rnd.next(0, 1) ? "S" : "NS", w);
    } else if (mode == 1) {
        int n = rnd.next(2, 8);
        a = rnd.next(1LL, 40LL);
        b = rnd.next(a, a + rnd.next(5LL, 50LL));
        set<long long> used;
        while ((int)cows.size() < n) {
            long long w = rnd.next(1LL, 80LL);
            if (used.insert(w).second) {
                addCow(rnd.next(0, 1) ? "S" : "NS", w);
            }
        }
    } else if (mode == 2) {
        long long left = rnd.next(1LL, 80LL);
        long long gap = rnd.next(1LL, 20LL);
        long long right = left + gap;
        a = max(1LL, left - rnd.next(0LL, 3LL));
        b = min(LIM, right + rnd.next(0LL, 3LL));
        addCow(rnd.next(0, 1) ? "S" : "NS", left);
        addCow(rnd.next(0, 1) ? "S" : "NS", right);
        int extra = rnd.next(0, 4);
        set<long long> used = {left, right};
        while (extra--) {
            long long w = rnd.next(1LL, 120LL);
            if (used.insert(w).second) {
                addCow(rnd.next(0, 1) ? "S" : "NS", w);
            }
        }
    } else if (mode == 3) {
        int n = rnd.next(3, 10);
        long long base = rnd.next(900000000LL, 999999950LL);
        a = rnd.next(base - 20, base);
        b = rnd.next(a, min(LIM, base + rnd.next(20LL, 50LL)));
        set<long long> used;
        while ((int)cows.size() < n) {
            long long w = rnd.next(base - 30, min(LIM, base + 60));
            if (used.insert(w).second) {
                addCow(rnd.next(0, 1) ? "S" : "NS", w);
            }
        }
    } else {
        int n = rnd.next(8, 16);
        a = rnd.next(1LL, 120LL);
        b = rnd.next(a, a + rnd.next(20LL, 120LL));
        set<long long> used;
        while ((int)cows.size() < n) {
            long long w = rnd.next(1LL, 180LL);
            if (used.insert(w).second) {
                addCow(rnd.next(0, 2) == 0 ? "S" : "NS", w);
            }
        }
    }

    shuffle(cows.begin(), cows.end());

    println((int)cows.size(), a, b);
    for (const auto& cow : cows) {
        println(cow.first, cow.second);
    }

    return 0;
}
