#include "testlib.h"

#include <algorithm>
#include <climits>
#include <tuple>
#include <vector>

using namespace std;

int validId(int n) {
    return rnd.next(1, n);
}

int noisyId(int n) {
    int mode = rnd.next(0, 7);
    if (mode == 0) return 0;
    if (mode == 1) return n + rnd.next(1, 4);
    if (mode == 2) return -rnd.next(1, 4);
    if (mode == 3) return INT_MIN;
    if (mode == 4) return INT_MAX;
    return validId(n);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = (mode == 0 ? 1 : rnd.next(2, 18));
    int k = (mode == 0 ? 0 : rnd.next(1, 35));
    vector<tuple<int, int, int>> records;

    if (mode == 1) {
        vector<int> species(n + 1);
        for (int i = 1; i <= n; ++i) species[i] = rnd.next(0, 2);

        for (int i = 0; i < k; ++i) {
            int x = validId(n);
            int y = validId(n);
            int rel = (species[x] - species[y] + 3) % 3;
            int t = (rel == 0 ? 1 : 2);
            if (rel == 2) swap(x, y);
            records.emplace_back(t, x, y);
        }
    } else if (mode == 2) {
        for (int i = 1; i <= min(n - 1, k); ++i) {
            int t = rnd.next(1, 2);
            records.emplace_back(t, i, i + 1);
        }
        while ((int)records.size() < k) {
            int x = validId(n);
            int y = validId(n);
            int t = rnd.next(1, 2);
            if (rnd.next(0, 3) == 0) y = x;
            records.emplace_back(t, x, y);
        }
    } else if (mode == 3) {
        int a = validId(n);
        int b = validId(n);
        while (b == a && n > 1) b = validId(n);

        records.emplace_back(1, a, b);
        records.emplace_back(2, a, b);
        records.emplace_back(2, a, a);
        while ((int)records.size() < k) {
            int t = rnd.next(1, 2);
            int x = validId(n);
            int y = validId(n);
            records.emplace_back(t, x, y);
        }
    } else if (mode == 4) {
        for (int i = 0; i < k; ++i) {
            records.emplace_back(rnd.next(1, 2), noisyId(n), noisyId(n));
        }
    } else {
        for (int i = 0; i < k; ++i) {
            int t = rnd.next(1, 2);
            int x = (rnd.next(0, 4) == 0 ? noisyId(n) : validId(n));
            int y = (rnd.next(0, 4) == 0 ? noisyId(n) : validId(n));
            records.emplace_back(t, x, y);
        }
    }

    if ((int)records.size() > k) records.resize(k);
    shuffle(records.begin(), records.end());

    println(n, (int)records.size());
    for (auto [t, x, y] : records) {
        println(t, x, y);
    }

    return 0;
}
