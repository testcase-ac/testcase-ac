#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

long long randomT(int mode, int l) {
    if (mode == 0) {
        return rnd.next(1, max(1, l + 3));
    }
    if (mode == 1) {
        return rnd.next(1, 6) * 1LL * l + rnd.next(0, l - 1);
    }
    if (mode == 2) {
        return 1000000000000000000LL - rnd.next(0, 20);
    }
    return rnd.next(1LL, 1000000000000LL);
}

int randomValue(int n, int i, int mode) {
    if (mode == 0) {
        return rnd.next(0, 255);
    }
    if (mode == 1) {
        return 1 << rnd.next(0, 7);
    }
    if (mode == 2) {
        return (i % 2 == 0 ? 0 : 255);
    }
    if (n == 1) {
        return rnd.next(0, 255);
    }
    return rnd.next(0, 15) | (rnd.next(0, 1) ? 128 : 0);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 14);
    int l = rnd.next(1, 24);

    if (mode == 0) {
        n = rnd.next(1, 4);
        l = rnd.next(1, 8);
    } else if (mode == 1) {
        n = rnd.next(2, 14);
        l = rnd.next(n - 1, min(24, 2 * n));
    } else if (mode == 2) {
        n = rnd.next(2, 12);
        l = rnd.next(n, min(24, 3 * n));
    } else if (mode == 3) {
        n = rnd.next(3, 10);
        l = rnd.next(n, min(24, n * (n - 1)));
    } else if (mode == 4) {
        n = rnd.next(1, 8);
        l = rnd.next(1, 16);
    }

    vector<pair<int, int>> ops;
    if (mode == 0) {
        for (int i = 0; i < l; ++i) {
            int a = rnd.next(1, n);
            int b = rnd.next(1, n);
            if (rnd.next(0, 2) == 0) {
                b = a;
            }
            ops.push_back({a, b});
        }
    } else if (mode == 1) {
        for (int i = 1; i < n; ++i) {
            ops.push_back({i + 1, i});
        }
        while ((int)ops.size() < l) {
            int a = rnd.next(1, n);
            int b = max(1, a - rnd.next(0, min(3, a - 1)));
            ops.push_back({a, b});
        }
    } else if (mode == 2) {
        for (int i = 1; i <= n; ++i) {
            ops.push_back({i, i % n + 1});
        }
        while ((int)ops.size() < l) {
            int a = rnd.next(1, n);
            int b = rnd.next(1, n);
            ops.push_back({a, b});
        }
    } else if (mode == 3) {
        vector<pair<int, int>> candidates;
        for (int a = 1; a <= n; ++a) {
            for (int b = 1; b <= n; ++b) {
                if (a != b) {
                    candidates.push_back({a, b});
                }
            }
        }
        shuffle(candidates.begin(), candidates.end());
        for (int i = 0; i < l; ++i) {
            ops.push_back(candidates[i]);
        }
    } else {
        for (int i = 0; i < l; ++i) {
            int a = (i % n) + 1;
            int b = rnd.next(1, n);
            if (rnd.next(0, 3) == 0) {
                b = a;
            }
            ops.push_back({a, b});
        }
    }

    if (rnd.next(0, 1)) {
        shuffle(ops.begin(), ops.end());
    }

    long long t = randomT(rnd.next(0, 3), l);
    println(n, l, t);
    for (auto [a, b] : ops) {
        println(a, b);
    }

    vector<int> x(n);
    int valueMode = rnd.next(0, 3);
    for (int i = 0; i < n; ++i) {
        x[i] = randomValue(n, i, valueMode);
    }
    println(x);

    return 0;
}
