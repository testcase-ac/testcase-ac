#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

long long bounded(long long x) {
    return max(-1000000000LL, min(1000000000LL, x));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(6);
    int n;
    if (mode == 0) {
        n = rnd.next(1, 3);
    } else if (mode == 5) {
        n = rnd.next(16, 18);
    } else {
        n = rnd.next(4, 12);
    }

    vector<vector<long long>> s(n, vector<long long>(n));
    long long smallLimit = rnd.next(3, 200);

    if (mode == 0) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                s[i][j] = rnd.next(-10, 10);
            }
        }
    } else if (mode == 1) {
        long long sign = rnd.next(2) == 0 ? -1 : 1;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                s[i][j] = sign * rnd.next(0, (int)smallLimit);
            }
        }
    } else if (mode == 2) {
        long long hi = rnd.next(900000000, 1000000000);
        long long lo = -rnd.next(900000000, 1000000000);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                s[i][j] = ((i + j + rnd.next(2)) % 2 == 0) ? hi : lo;
            }
        }
    } else if (mode == 3) {
        vector<long long> row(n), col(n);
        for (int i = 0; i < n; ++i) row[i] = rnd.next(-500000, 500000);
        for (int j = 0; j < n; ++j) col[j] = rnd.next(-500000, 500000);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                long long noise = rnd.next(-1000, 1000);
                s[i][j] = bounded(row[i] + col[j] + noise);
            }
        }
    } else if (mode == 4) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (rnd.next(100) < 75) {
                    s[i][j] = 0;
                } else {
                    s[i][j] = rnd.next(2) == 0 ? -1000000000LL : 1000000000LL;
                }
            }
        }
    } else {
        int limit = rnd.next(1000, 1000000000);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                s[i][j] = rnd.next(-limit, limit);
            }
        }
    }

    println(n);
    for (int i = 0; i < n; ++i) {
        println(s[i]);
    }

    return 0;
}
