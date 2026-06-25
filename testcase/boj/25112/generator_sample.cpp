#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

int travelTimeForMode(int mode, int i, int n) {
    if (mode == 0) return rnd.next(1, 20);
    if (mode == 1) return (i % 2 == 0 ? rnd.next(1, 5) : rnd.next(900000, 1000000));
    if (mode == 2) return max(1, 1000 - abs(2 * i - n) * rnd.next(1, 20));
    return rnd.any(vector<int>{1, 2, 999999, 1000000});
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = 2;
    } else if (mode == 1) {
        n = rnd.next(3, 6);
    } else {
        n = rnd.next(7, 16);
    }

    vector<int> t(n - 1);
    for (int i = 0; i < n - 1; ++i) {
        t[i] = travelTimeForMode(mode % 4, i, n);
    }

    int k;
    if (mode == 0) {
        k = rnd.next(0, 1);
    } else if (mode == 4) {
        k = rnd.next(n, 2 * n);
    } else {
        k = rnd.next(1, min(12, 2 * n));
    }

    vector<pair<int, int>> updates;
    int hotSection = rnd.next(1, n - 1);
    for (int i = 0; i < k; ++i) {
        int section;
        if (mode == 3 || (mode == 4 && rnd.next(0, 2) > 0)) {
            section = hotSection;
        } else if (mode == 5) {
            section = 1 + (i % (n - 1));
        } else {
            section = rnd.next(1, n - 1);
        }

        int updatedTime;
        if (mode == 1) {
            updatedTime = rnd.any(vector<int>{1, 2, 999999, 1000000});
        } else if (mode == 2) {
            updatedTime = rnd.next(450, 1550);
        } else {
            updatedTime = rnd.next(1, 1000000);
        }
        updates.push_back({section, updatedTime});
    }

    println(n);
    println(t);
    println(k);
    for (const auto& update : updates) {
        println(update.first, update.second);
    }

    return 0;
}
