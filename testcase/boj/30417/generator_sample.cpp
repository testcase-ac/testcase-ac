#include "testlib.h"

#include <algorithm>
#include <set>
#include <vector>

using namespace std;

struct Cookie {
    int x;
    int r;
    int c;
};

int boundedRadius(int n, int x, int mode) {
    if (mode == 0) return 0;
    if (mode == 1) return rnd.next(0, min(n, 2));
    if (mode == 2) return rnd.next(0, min(n, 6));
    if (mode == 3) return rnd.next(max(0, min(n, abs(x - (n + 1) / 2) - 1)), n);
    return rnd.next(0, n);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n;
    int k;

    if (mode == 0) {
        n = rnd.next(1, 8);
        k = rnd.next(1, n);
    } else if (mode == 1) {
        n = rnd.next(6, 18);
        k = rnd.next(max(1, n / 2), n);
    } else if (mode == 2) {
        n = rnd.next(8, 30);
        k = rnd.next(2, min(n, 10));
    } else if (mode == 3) {
        n = rnd.next(10, 40);
        k = rnd.next(3, min(n, 12));
    } else {
        n = rnd.next(20, 80);
        k = rnd.next(1, min(n, 15));
    }

    vector<int> positions;
    if (mode == 1) {
        int start = rnd.next(1, n - k + 1);
        for (int i = 0; i < k; ++i) positions.push_back(start + i);
    } else if (mode == 2) {
        int gap = max(1, n / k);
        for (int i = 0; i < k; ++i) {
            int lo = min(n, i * gap + 1);
            int hi = min(n, max(lo, (i + 1) * gap));
            positions.push_back(rnd.next(lo, hi));
        }
        sort(positions.begin(), positions.end());
        positions.erase(unique(positions.begin(), positions.end()), positions.end());
        while ((int)positions.size() < k) {
            int x = rnd.next(1, n);
            if (find(positions.begin(), positions.end(), x) == positions.end()) positions.push_back(x);
        }
    } else {
        set<int> used;
        while ((int)positions.size() < k) {
            int x = rnd.next(1, n);
            if (used.insert(x).second) positions.push_back(x);
        }
    }

    shuffle(positions.begin(), positions.end());

    vector<Cookie> cookies;
    int radiusMode = rnd.next(0, 4);
    for (int x : positions) {
        int r = boundedRadius(n, x, radiusMode);
        int priceMode = rnd.next(0, 3);
        int c;
        if (priceMode == 0) {
            c = rnd.next(1, 9);
        } else if (priceMode == 1) {
            c = rnd.next(990, 1000);
        } else if (priceMode == 2) {
            c = rnd.next(1, 1000);
        } else {
            c = (x % 2 == 0) ? rnd.next(1, 20) : rnd.next(500, 1000);
        }
        cookies.push_back({x, r, c});
    }

    if (rnd.next(0, 1)) {
        sort(cookies.begin(), cookies.end(),
             [](const Cookie& a, const Cookie& b) { return a.x < b.x; });
    }

    println(n, k);
    for (const Cookie& cookie : cookies) {
        println(cookie.x, cookie.r, cookie.c);
    }

    return 0;
}
