#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int clampHeight(long long value) {
    return int(max(1LL, min(1000000000LL, value)));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n = 1;
    if (mode == 0) {
        n = 1;
    } else if (mode <= 2) {
        n = rnd.next(2, 5);
    } else {
        n = rnd.next(3, 12);
    }

    vector<vector<int>> a(n, vector<int>(n, 1));

    if (mode == 0) {
        a[0][0] = rnd.next(1, 1000000000);
    } else if (mode == 1) {
        int h = rnd.next(1, 1000000000);
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < n; ++c) {
                a[r][c] = h;
            }
        }
    } else if (mode == 2) {
        int low = rnd.next(1, 50);
        int high = rnd.next(999999950, 1000000000);
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < n; ++c) {
                a[r][c] = ((r + c) % 2 == 0 ? low : high);
            }
        }
    } else if (mode == 3) {
        int base = rnd.next(1, 999999000);
        int rowStep = rnd.next(0, 80);
        int colStep = rnd.next(0, 80);
        int noise = rnd.next(0, 12);
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < n; ++c) {
                a[r][c] = clampHeight(base + 1LL * r * rowStep + 1LL * c * colStep + rnd.next(-noise, noise));
            }
        }
    } else if (mode == 4) {
        int low = rnd.next(1, 1000);
        int wall = rnd.next(999999000, 1000000000);
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < n; ++c) {
                a[r][c] = low + rnd.next(0, 5);
            }
        }
        int wallRow = rnd.next(0, n - 2);
        for (int c = 0; c < n; ++c) {
            a[wallRow][c] = wall - rnd.next(0, 5);
        }
        int gap = rnd.next(0, n - 1);
        a[wallRow][gap] = low + rnd.next(0, 5);
    } else if (mode == 5) {
        int start = rnd.next(1, 1000000);
        int step = rnd.next(0, 20);
        int high = rnd.next(500000000, 1000000000);
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < n; ++c) {
                a[r][c] = high - rnd.next(0, 1000);
            }
        }
        int order = 0;
        for (int r = 0; r < n; ++r) {
            if (r % 2 == 0) {
                for (int c = 0; c < n; ++c) {
                    a[r][c] = clampHeight(start + 1LL * order++ * step);
                }
            } else {
                for (int c = n - 1; c >= 0; --c) {
                    a[r][c] = clampHeight(start + 1LL * order++ * step);
                }
            }
        }
    } else if (mode == 6) {
        int clusters = rnd.next(2, 5);
        vector<int> center(clusters);
        for (int i = 0; i < clusters; ++i) {
            center[i] = rnd.next(1, 1000000000);
        }
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < n; ++c) {
                int id = rnd.next(0, clusters - 1);
                a[r][c] = clampHeight(center[id] + rnd.next(-30, 30));
            }
        }
    } else {
        int lo = rnd.next(1, 1000);
        int hi = rnd.next(999999000, 1000000000);
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < n; ++c) {
                if (r == 0 || c == n - 1) {
                    a[r][c] = lo + rnd.next(0, 10);
                } else {
                    a[r][c] = hi - rnd.next(0, 10);
                }
            }
        }
    }

    println(n);
    for (int r = 0; r < n; ++r) {
        println(a[r]);
    }

    return 0;
}
