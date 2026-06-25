#include "testlib.h"
#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(3, 14);
    vector<vector<int>> a(n, vector<int>(n, 0));

    if (mode == 0) {
        int hi = rnd.next(0, 30);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                a[i][j] = rnd.next(0, hi);
            }
        }
    } else if (mode == 1) {
        int rowStep = rnd.next(0, 12);
        int colStep = rnd.next(0, 12);
        int base = rnd.next(0, 10);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                a[i][j] = base + rowStep * i + colStep * j + rnd.next(0, 3);
            }
        }
    } else if (mode == 2) {
        int spikes = rnd.next(1, min(8, n * n));
        for (int t = 0; t < spikes; ++t) {
            int i = rnd.next(0, n - 1);
            int j = rnd.next(0, n - 1);
            a[i][j] = rnd.next(50, 1000);
        }
    } else if (mode == 3) {
        int band = rnd.next(0, n - 1);
        bool horizontal = rnd.next(0, 1);
        int high = rnd.next(20, 500);
        int low = rnd.next(0, 5);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                a[i][j] = (horizontal ? i == band : j == band) ? high + rnd.next(0, 20) : low;
            }
        }
    } else if (mode == 4) {
        int value = rnd.next(0, 100);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                a[i][j] = value;
            }
        }
    } else {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                a[i][j] = rnd.next(0, 10000000);
            }
        }
    }

    long long sum = 0;
    int mx = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            sum += a[i][j];
            mx = max(mx, a[i][j]);
        }
    }

    long long r;
    int target = rnd.next(0, 4);
    if (target == 0) {
        r = 1;
    } else if (target == 1) {
        r = max(1, mx);
    } else if (target == 2) {
        r = max(1LL, sum / 2 + rnd.next(0, 20));
    } else if (target == 3) {
        r = max(1LL, sum + rnd.next(0, 50));
    } else {
        r = rnd.next(1LL, 1000000000000LL);
    }

    println(n, r);
    for (int i = 0; i < n; ++i) {
        println(a[i]);
    }

    return 0;
}
