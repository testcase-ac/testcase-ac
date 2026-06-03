#include "testlib.h"
#include <algorithm>
#include <vector>

using namespace std;

struct Triple {
    int n;
    int m;
    int k;
};

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<Triple> candidates;

    auto add = [&](int n, int m, int k) {
        if (1 <= n && n <= 2000 && 1 <= m && m <= 2000 && 1 <= k && k <= 2000 && n > m * (k - 1)) {
            candidates.push_back({n, m, k});
        }
    };

    int mode = rnd.next(0, 7);

    if (mode == 0) {
        int n = rnd.next(1, 30);
        int m = rnd.next(1, 30);
        int k = rnd.next(1, min(30, (n - 1) / m + 1));
        add(n, m, k);
    } else if (mode == 1) {
        int m = rnd.next(1, 25);
        int k = rnd.next(1, 20);
        int base = m * (k - 1);
        add(base + rnd.next(1, min(25, 2000 - base)), m, k);
    } else if (mode == 2) {
        int n = rnd.next(1, 80);
        int k = rnd.next(1, 10);
        int maxM = k == 1 ? 80 : max(1, (n - 1) / (k - 1));
        int m = rnd.next(1, min(80, maxM));
        add(n, m, k);
    } else if (mode == 3) {
        int n = rnd.next(1, 2000);
        int m = rnd.next(1500, 2000);
        add(n, m, 1);
    } else if (mode == 4) {
        int m = rnd.next(1, 44);
        int k = rnd.next(2, 44);
        add(m * (k - 1) + 1, m, k);
    } else if (mode == 5) {
        int m = rnd.next(1, 2000);
        int k = rnd.next(1, min(2000, (1999 / m) + 1));
        add(2000, m, k);
    } else if (mode == 6) {
        int n = rnd.any(vector<int>{1, 2, 10, 1000, 1999, 2000});
        int m = rnd.any(vector<int>{1, 2, 5, 9, 1999, 2000});
        int k = rnd.next(1, min(2000, (n - 1) / m + 1));
        add(n, m, k);
    } else {
        int n = rnd.next(1, 120);
        int m = rnd.next(1, 120);
        add(n, m, 1);
    }

    if (candidates.empty()) {
        add(1, 1, 1);
    }

    Triple t = rnd.any(candidates);
    println(t.n, t.m, t.k);

    return 0;
}
