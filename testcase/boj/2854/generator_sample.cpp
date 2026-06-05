#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n;
    if (mode == 7) {
        n = rnd.next(30, 80);
    } else {
        n = rnd.next(2, 14);
    }

    vector<long long> exact(n), adjacent(n - 1);

    auto smallValue = [&]() -> long long {
        return rnd.next(0, 8);
    };
    auto largeValue = [&]() -> long long {
        if (rnd.next(0, 4) == 0) return 1000000000LL;
        return rnd.next(900000000, 1000000000);
    };

    if (mode == 0) {
        for (int i = 0; i < n; ++i) exact[i] = smallValue();
        for (int i = 0; i + 1 < n; ++i) adjacent[i] = smallValue();
    } else if (mode == 1) {
        for (int i = 0; i < n; ++i) exact[i] = (i % 2 == 0 ? smallValue() : 0);
        for (int i = 0; i + 1 < n; ++i) adjacent[i] = (i % 2 == 1 ? smallValue() : 0);
    } else if (mode == 2) {
        int pos = rnd.next(0, n - 1);
        exact[pos] = rnd.next(1, 10);
        if (n > 2) adjacent[rnd.next(0, n - 2)] = rnd.next(1, 10);
    } else if (mode == 3) {
        for (int i = 0; i < n; ++i) exact[i] = rnd.next(0, 1);
        for (int i = 0; i + 1 < n; ++i) adjacent[i] = rnd.next(0, 1);
    } else if (mode == 4) {
        for (int i = 0; i < n; ++i) exact[i] = largeValue();
        for (int i = 0; i + 1 < n; ++i) adjacent[i] = rnd.next(0, 3) == 0 ? largeValue() : smallValue();
    } else if (mode == 5) {
        long long base = rnd.next(0, 20);
        for (int i = 0; i < n; ++i) exact[i] = base + rnd.next(0, 3);
        for (int i = 0; i + 1 < n; ++i) adjacent[i] = base + rnd.next(0, 3);
    } else if (mode == 6) {
        for (int i = 0; i < n; ++i) exact[i] = rnd.next(0, 20);
        for (int i = 0; i + 1 < n; ++i) adjacent[i] = i == 0 || i == n - 2 ? rnd.next(0, 20) : rnd.next(0, 2);
    } else {
        for (int i = 0; i < n; ++i) exact[i] = rnd.next(0, 100);
        for (int i = 0; i + 1 < n; ++i) adjacent[i] = rnd.next(0, 100);
    }

    println(n);
    println(exact);
    println(adjacent);
    return 0;
}
