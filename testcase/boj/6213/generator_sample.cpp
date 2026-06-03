#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

vector<int> makeHeights(int n, int mode) {
    vector<int> h(n);

    if (mode == 0) {
        int value = rnd.next(1, 1000000);
        fill(h.begin(), h.end(), value);
    } else if (mode == 1) {
        int lo = rnd.next(1, 20);
        int hi = rnd.next(999981, 1000000);
        for (int i = 0; i < n; ++i) {
            h[i] = (i % 2 == 0 ? lo + rnd.next(0, 19) : hi - rnd.next(0, 19));
        }
    } else if (mode == 2) {
        int cur = rnd.next(1, 100);
        int step = rnd.next(1, 30);
        for (int i = 0; i < n; ++i) {
            h[i] = min(1000000, cur + i * step + rnd.next(0, 5));
        }
        if (rnd.next(0, 1) == 0) {
            reverse(h.begin(), h.end());
        }
    } else if (mode == 3) {
        int center = rnd.next(20, 999980);
        int spread = rnd.next(1, 50);
        for (int i = 0; i < n; ++i) {
            h[i] = center + rnd.next(-spread, spread);
        }
    } else {
        int low = rnd.next(1, 1000);
        int high = rnd.next(999000, 1000000);
        for (int i = 0; i < n; ++i) {
            int pick = rnd.next(0, 9);
            if (pick < 4) {
                h[i] = low + rnd.next(0, 100);
            } else if (pick < 8) {
                h[i] = high - rnd.next(0, 100);
            } else {
                h[i] = rnd.next(1, 1000000);
            }
        }
    }

    for (int& x : h) {
        x = max(1, min(1000000, x));
    }
    return h;
}

pair<int, int> makeQuery(int n, int mode) {
    if (mode == 0) {
        int a = rnd.next(1, n);
        return {a, a};
    }
    if (mode == 1) {
        return {1, n};
    }
    if (mode == 2) {
        int a = rnd.next(1, n);
        int b = min(n, a + rnd.next(0, min(4, n - a)));
        return {a, b};
    }
    if (mode == 3) {
        int len = rnd.next(max(1, n / 2), n);
        int a = rnd.next(1, n - len + 1);
        return {a, a + len - 1};
    }

    int a = rnd.next(1, n);
    int b = rnd.next(a, n);
    return {a, b};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    int q;

    if (mode == 0) {
        n = rnd.next(1, 3);
        q = rnd.next(1, 6);
    } else if (mode == 5) {
        n = rnd.next(35, 80);
        q = rnd.next(60, 140);
    } else {
        n = rnd.next(4, 30);
        q = rnd.next(n, n * 3);
    }

    vector<int> h = makeHeights(n, mode % 5);
    vector<pair<int, int>> queries;
    queries.reserve(q);

    if (n > 1 && (int)queries.size() < q) {
        queries.push_back({1, n});
    }
    if ((int)queries.size() < q) {
        queries.push_back({rnd.next(1, n), rnd.next(1, n)});
        if (queries.back().first > queries.back().second) {
            swap(queries.back().first, queries.back().second);
        }
    }

    while ((int)queries.size() < q) {
        queries.push_back(makeQuery(n, rnd.next(0, 4)));
    }
    shuffle(queries.begin(), queries.end());

    println(n, q);
    for (int x : h) {
        println(x);
    }
    for (auto [a, b] : queries) {
        println(a, b);
    }

    return 0;
}
