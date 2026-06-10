#include "testlib.h"

#include <utility>
#include <vector>

using namespace std;

int boundedValue(int base, int spread) {
    int lo = max(0, base - spread);
    int hi = min(1000, base + spread);
    return rnd.next(lo, hi);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = 3;
    } else if (mode <= 3) {
        n = rnd.next(4, 12);
    } else {
        n = rnd.next(13, 30);
    }

    int m = rnd.next(n, min(100, 4 * n));
    vector<int> a(n), b(n);

    if (mode == 0) {
        for (int i = 0; i < n; ++i) {
            a[i] = rnd.any(vector<int>{0, 1, 999, 1000});
            b[i] = rnd.any(vector<int>{0, 1, 999, 1000});
        }
    } else if (mode == 1) {
        int base = rnd.next(0, 1000);
        int spread = rnd.next(0, 8);
        for (int i = 0; i < n; ++i) {
            a[i] = boundedValue(base, spread);
            b[i] = boundedValue(base + rnd.next(-5, 5), spread + 5);
        }
    } else if (mode == 2) {
        for (int i = 0; i < n; ++i) {
            a[i] = rnd.next(0, 40);
            b[i] = rnd.next(960, 1000);
        }
    } else if (mode == 3) {
        for (int i = 0; i < n; ++i) {
            a[i] = rnd.next(960, 1000);
            b[i] = rnd.next(0, 40);
        }
    } else {
        for (int i = 0; i < n; ++i) {
            int total = rnd.next(0, 1000);
            a[i] = total;
            b[i] = rnd.next(max(0, total - 150), min(1000, total + 150));
        }
    }

    vector<vector<int>> queries;
    bool hasTypeTwo = false;
    int nextChain = 1;

    for (int i = 0; i < m; ++i) {
        bool putAsk = false;
        if (!hasTypeTwo && i == m - 1) putAsk = true;
        if (!putAsk && rnd.next(100) < 25) putAsk = true;

        if (putAsk) {
            queries.push_back({2});
            hasTypeTwo = true;
            continue;
        }

        int x, y;
        int qmode = rnd.next(0, 4);
        if (qmode == 0 && nextChain < n) {
            x = nextChain;
            y = nextChain + 1;
            ++nextChain;
        } else if (qmode == 1) {
            x = 1;
            y = rnd.next(1, n);
        } else if (qmode == 2) {
            x = rnd.next(1, n);
            y = x;
        } else if (qmode == 3) {
            x = rnd.next(1, n);
            y = rnd.next(1, n);
        } else {
            x = rnd.next(1, n);
            y = n - x + 1;
        }
        queries.push_back({1, x, y});
    }

    println(n, m);
    println(a);
    println(b);
    for (const auto& query : queries) {
        println(query);
    }

    return 0;
}
