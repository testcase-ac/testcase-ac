#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

long long signedValue(long long limit) {
    long long value = rnd.next(0LL, limit);
    if (rnd.next(2) == 0) value = -value;
    return value;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(7);
    int n;
    if (mode == 4) {
        n = 9;
    } else if (mode == 0) {
        n = rnd.next(1, 3);
    } else {
        n = rnd.next(2, 9);
    }

    vector<vector<long long>> s(n, vector<long long>(n, 0));

    if (mode == 0) {
        long long value = signedValue(20);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                s[i][j] = value;
    } else if (mode == 1) {
        long long limit = rnd.next(3, 200);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                s[i][j] = signedValue(limit);
    } else if (mode == 2) {
        long long high = rnd.next(100000000LL, 1000000000LL);
        long long low = rnd.next(0LL, 30LL);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                long long value = ((i + j) % 2 == 0 ? high : low);
                if (rnd.next(4) == 0) value = -value;
                s[i][j] = value;
            }
        }
    } else if (mode == 3) {
        vector<long long> row(n), col(n);
        for (int i = 0; i < n; ++i) row[i] = signedValue(1000);
        for (int j = 0; j < n; ++j) col[j] = signedValue(1000);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                s[i][j] = row[i] + col[j] + signedValue(5);
    } else if (mode == 4) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (rnd.next(5) == 0) {
                    s[i][j] = 0;
                } else {
                    s[i][j] = rnd.next(2) == 0 ? -1000000000LL : 1000000000LL;
                }
            }
        }
    } else if (mode == 5) {
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                if (rnd.next(3) == 0) s[i][j] = signedValue(1000000000LL);
    } else {
        for (int i = 0; i < n; ++i) {
            for (int j = i; j < n; ++j) {
                long long value = signedValue(5000);
                s[i][j] = value;
                s[j][i] = rnd.next(4) == 0 ? -value : value;
            }
        }
    }

    println(n);
    for (int i = 0; i < n; ++i) println(s[i]);

    return 0;
}
