#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

long long insertionChangeCount(const vector<int>& a) {
    long long changes = 0;
    vector<int> sorted;
    for (int x : a) {
        int greater = 0;
        for (int y : sorted) {
            if (y > x) ++greater;
        }
        if (greater > 0) changes += greater + 1;
        sorted.insert(lower_bound(sorted.begin(), sorted.end(), x), x);
    }
    return changes;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n;
    if (mode == 6) {
        n = rnd.next(80, 160);
    } else {
        n = rnd.next(5, 35);
    }

    vector<int> p(n);
    iota(p.begin(), p.end(), 1);

    if (mode == 0) {
        // Already sorted: no changes happen, regardless of K.
    } else if (mode == 1) {
        reverse(p.begin(), p.end());
    } else if (mode == 2) {
        int swaps = rnd.next(1, max(1, n / 3));
        for (int i = 0; i < swaps; ++i) {
            int at = rnd.next(0, n - 2);
            swap(p[at], p[at + 1]);
        }
    } else if (mode == 3) {
        int cut = rnd.next(1, n - 1);
        rotate(p.begin(), p.begin() + cut, p.end());
    } else if (mode == 4) {
        shuffle(p.begin(), p.end());
    } else if (mode == 5) {
        reverse(p.begin(), p.end());
        int tail = rnd.next(1, min(n - 1, 8));
        shuffle(p.end() - tail, p.end());
    } else {
        shuffle(p.begin(), p.end());
    }

    int base;
    if (rnd.next(0, 3) == 0) {
        base = 1000000000 - n - rnd.next(0, 1000);
    } else {
        base = rnd.next(1, 1000);
    }

    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        a[i] = base + p[i] - 1;
    }

    long long totalChanges = insertionChangeCount(a);
    long long k;
    int kMode = rnd.next(0, 5);
    if (kMode == 0) {
        k = 1;
    } else if (kMode == 1) {
        k = rnd.next(1LL, 20LL);
    } else if (kMode == 2 && totalChanges > 0) {
        k = rnd.next(1LL, totalChanges);
    } else if (kMode == 3) {
        k = min(1000000000000LL, totalChanges + rnd.next(1LL, 20LL));
    } else if (kMode == 4 && totalChanges > 0) {
        k = totalChanges;
    } else {
        k = 1000000000000LL;
    }

    println(n, k);
    println(a);

    return 0;
}
