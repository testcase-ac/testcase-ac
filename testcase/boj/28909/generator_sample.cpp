#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int clampCapacity(int x) {
    return max(1, min(1000, x));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = rnd.next(1, 20);
    int m = rnd.next(1, 28);
    int k = rnd.next(0, n);

    if (mode == 0) {
        n = rnd.next(1, 8);
        m = rnd.next(n, n + 12);
        k = rnd.any(vector<int>{0, n, rnd.next(0, n)});
    } else if (mode == 1) {
        n = rnd.next(2, 16);
        m = rnd.next(n, n + 10);
        k = rnd.next(0, n);
    } else if (mode == 2) {
        n = rnd.next(3, 18);
        m = rnd.next(1, 24);
        k = rnd.next(1, n - 1);
    } else if (mode == 3) {
        n = rnd.next(8, 30);
        m = rnd.next(12, 40);
        k = rnd.next(0, n);
    }

    vector<int> a(n);
    int base = rnd.next(1, 980);
    if (mode == 0) {
        for (int i = 0; i < n; ++i) a[i] = clampCapacity(base + rnd.next(0, 3));
    } else if (mode == 1) {
        for (int i = 0; i < n; ++i) {
            int distance = i + 1 <= k ? k - (i + 1) : (i + 1) - k - 1;
            a[i] = clampCapacity(base + distance % 5);
        }
    } else if (mode == 2) {
        for (int i = 0; i < n; ++i) a[i] = clampCapacity(base + (i % 2 == 0 ? 0 : 1));
        for (int i = 0; i < n / 3; ++i) a[rnd.next(0, n - 1)] = clampCapacity(base + rnd.next(2, 8));
    } else {
        for (int i = 0; i < n; ++i) a[i] = rnd.next(1, 1000);
    }

    vector<int> b;
    b.reserve(m);
    for (int j = 0; j < m; ++j) {
        int pick = rnd.next(0, 99);
        if (pick < 50) {
            b.push_back(rnd.any(a));
        } else if (pick < 75) {
            b.push_back(clampCapacity(rnd.any(a) - rnd.next(0, 3)));
        } else if (pick < 90) {
            b.push_back(clampCapacity(rnd.any(a) + rnd.next(1, 5)));
        } else {
            b.push_back(rnd.next(1, 1000));
        }
    }

    if (m >= n + 2) {
        for (int j = n; j < m; ++j) {
            if (rnd.next(0, 2) == 0) b[j] = 1000;
        }
    }

    println(n, m, k);
    println(a);
    println(b);

    return 0;
}
