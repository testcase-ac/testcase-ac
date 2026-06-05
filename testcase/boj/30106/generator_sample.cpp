#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

const long long MAX_A = 1000000000LL;

long long clampHeight(long long x) {
    return max(1LL, min(MAX_A, x));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 10);
    int m = rnd.next(1, 10);

    if (mode == 1) {
        n = rnd.next(1, 3);
        m = rnd.next(1, 14);
    } else if (mode == 2) {
        n = rnd.next(1, 14);
        m = rnd.next(1, 3);
    } else if (mode == 5) {
        n = rnd.next(8, 16);
        m = rnd.next(8, 16);
    }

    long long k;
    if (mode == 3) {
        k = rnd.next(1, 3);
    } else if (mode == 4) {
        k = rnd.any(vector<long long>{1LL, 2LL, 1000000000LL});
    } else {
        k = rnd.next(1LL, 30LL);
    }

    vector<vector<long long>> a(n, vector<long long>(m, 1));

    if (mode == 0) {
        long long base = rnd.next(1LL, MAX_A - 1000);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                a[i][j] = base + rnd.next(0LL, k);
            }
        }
    } else if (mode == 1) {
        long long low = rnd.next(1LL, 100LL);
        long long high = clampHeight(low + k + rnd.next(1LL, 20LL));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                a[i][j] = (j % 2 == 0 ? low : high) + rnd.next(0LL, min(k, 3LL));
                a[i][j] = clampHeight(a[i][j]);
            }
        }
    } else if (mode == 2) {
        long long cur = rnd.next(1LL, 200LL);
        for (int i = 0; i < n; ++i) {
            long long step = rnd.next(0, 2) == 0 ? k : k + rnd.next(1LL, 8LL);
            cur = clampHeight(cur + step);
            for (int j = 0; j < m; ++j) {
                a[i][j] = clampHeight(cur + rnd.next(0LL, min(k, 4LL)));
            }
        }
    } else if (mode == 3) {
        long long first = rnd.next(1LL, 100LL);
        long long second = clampHeight(first + k + 1);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                a[i][j] = ((i + j) % 2 == 0) ? first : second;
            }
        }
    } else if (mode == 4) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (rnd.next(0, 3) == 0) {
                    a[i][j] = rnd.any(vector<long long>{1LL, MAX_A});
                } else {
                    a[i][j] = rnd.next(1LL, MAX_A);
                }
            }
        }
    } else {
        int groups = rnd.next(2, 5);
        vector<long long> values;
        long long start = rnd.next(1LL, 1000LL);
        for (int g = 0; g < groups; ++g) {
            start = clampHeight(start + rnd.next(k + 1, k + 100));
            values.push_back(start);
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                int block = (i / rnd.next(2, 4) + j / rnd.next(2, 4)) % groups;
                a[i][j] = clampHeight(values[block] + rnd.next(0LL, min(k, 5LL)));
            }
        }
    }

    println(n, m, k);
    for (int i = 0; i < n; ++i) {
        println(a[i]);
    }

    return 0;
}
