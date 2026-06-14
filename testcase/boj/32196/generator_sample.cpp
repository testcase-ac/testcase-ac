#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <utility>
#include <vector>

using namespace std;

long long randomWeight() {
    int mode = rnd.next(0, 4);
    if (mode == 0) return 1;
    if (mode == 1) return rnd.next(1, 10);
    if (mode == 2) return rnd.next(900, 1100);
    if (mode == 3) return rnd.next(1000000, 10000000);
    return rnd.next(900000000, 1000000000);
}

int chooseSmallValue() {
    return rnd.any(vector<int>{0, 1, 2, 3, 10, 999, 1000, rnd.next(0, 1000)});
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = mode == 5 ? rnd.next(40, 120) : rnd.next(1, 20);
    int m;
    if (mode == 0) {
        m = 1;
    } else if (mode == 1) {
        m = n;
    } else {
        m = rnd.next(1, n);
    }

    long long x = randomWeight();
    long long y = randomWeight();
    if (mode == 2) {
        x = y;
    } else if (mode == 3) {
        x = rnd.next(1, 5);
        y = rnd.next(900000000, 1000000000);
    } else if (mode == 4) {
        x = rnd.next(900000000, 1000000000);
        y = rnd.next(1, 5);
    }

    vector<pair<int, int>> stations;
    stations.reserve(n);

    if (mode == 0) {
        for (int i = 0; i < n; ++i) {
            stations.push_back({chooseSmallValue(), chooseSmallValue()});
        }
    } else if (mode == 1) {
        for (int i = 0; i < n; ++i) {
            int a = rnd.next(0, 20);
            int b = rnd.next(0, 20);
            stations.push_back({a, b});
        }
    } else if (mode == 2) {
        int base = rnd.next(0, 1000);
        for (int i = 0; i < n; ++i) {
            int delta = rnd.next(0, min(base, 30));
            stations.push_back({base - delta, base - delta});
        }
    } else if (mode == 3) {
        for (int i = 0; i < n; ++i) {
            int b = rnd.any(vector<int>{0, 1, 999, 1000, rnd.next(0, 1000)});
            int a = rnd.next(0, 40);
            stations.push_back({a, b});
        }
    } else if (mode == 4) {
        for (int i = 0; i < n; ++i) {
            int a = rnd.any(vector<int>{0, 1, 999, 1000, rnd.next(0, 1000)});
            int b = rnd.next(0, 40);
            stations.push_back({a, b});
        }
    } else {
        int centerA = rnd.next(0, 1000);
        int centerB = rnd.next(0, 1000);
        for (int i = 0; i < n; ++i) {
            int a = max(0, min(1000, centerA + rnd.next(-25, 25)));
            int b = max(0, min(1000, centerB + rnd.next(-25, 25)));
            stations.push_back({a, b});
        }
    }

    shuffle(stations.begin(), stations.end());

    long long sumB = 0;
    for (auto [a, b] : stations) {
        sumB += b;
    }

    long long k;
    if (sumB == 0) {
        k = rnd.any(vector<long long>{1, rnd.next(1, 100), rnd.next(900000000, 1000000000)});
    } else if (rnd.next(0, 2) == 0) {
        k = sumB + 1;
    } else {
        k = rnd.next(sumB + 1, min(1000000000LL, sumB + rnd.next(1, 1000000)));
    }

    println(n, m, k, x, y);
    for (auto [a, b] : stations) {
        println(a, b);
    }

    return 0;
}
