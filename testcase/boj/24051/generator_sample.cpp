#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

long long insertionSaveCount(const vector<int>& a) {
    vector<int> b = a;
    long long saves = 0;

    for (int i = 1; i < static_cast<int>(b.size()); ++i) {
        int loc = i - 1;
        int newItem = b[i];
        while (loc >= 0 && newItem < b[loc]) {
            b[loc + 1] = b[loc];
            ++saves;
            --loc;
        }
        if (loc + 1 != i) {
            b[loc + 1] = newItem;
            ++saves;
        }
    }

    return saves;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(5, 20);
    vector<int> a(n);

    if (mode == 0) {
        iota(a.begin(), a.end(), 1);
    } else if (mode == 1) {
        iota(a.begin(), a.end(), 1);
        reverse(a.begin(), a.end());
    } else if (mode == 2) {
        iota(a.begin(), a.end(), 1);
        int moves = rnd.next(1, n / 2);
        for (int t = 0; t < moves; ++t) {
            int i = rnd.next(1, n - 1);
            int j = rnd.next(0, i - 1);
            rotate(a.begin() + j, a.begin() + i, a.begin() + i + 1);
        }
    } else if (mode == 3) {
        iota(a.begin(), a.end(), 1);
        shuffle(a.begin(), a.end());
    } else if (mode == 4) {
        int base = 1000000000 - n + 1;
        for (int i = 0; i < n; ++i) {
            a[i] = base + i;
        }
        shuffle(a.begin(), a.end());
    } else {
        int step = rnd.next(2, 20);
        int start = rnd.next(1, 1000);
        for (int i = 0; i < n; ++i) {
            a[i] = start + i * step;
        }
        shuffle(a.begin(), a.end());
    }

    long long saves = insertionSaveCount(a);
    long long k;
    int kMode = rnd.next(0, 3);
    if (kMode == 0) {
        k = rnd.next(1LL, max(1LL, saves));
    } else if (kMode == 1) {
        k = min(1LL * n * n, saves + rnd.next(1LL, 1LL * n));
    } else if (kMode == 2) {
        k = 1LL * n * n;
    } else {
        k = rnd.next(1LL, 1LL * n * n);
    }

    println(n, k);
    println(a);

    return 0;
}
