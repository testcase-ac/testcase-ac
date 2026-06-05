#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

const long long MAX_A = 1000000000LL;

vector<long long> splitSum(long long sum, int m) {
    vector<long long> row(m, 0);
    for (int j = 0; j < m; ++j) {
        long long remainingCells = m - j - 1;
        long long lo = max(0LL, sum - remainingCells * MAX_A);
        long long hi = min(MAX_A, sum);
        row[j] = rnd.next(lo, hi);
        sum -= row[j];
    }
    shuffle(row.begin(), row.end());
    return row;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n, m;
    vector<vector<long long>> a;

    if (mode == 0) {
        n = rnd.next(1, 3);
        m = rnd.next(1, 3);
        vector<long long> values = {0, 1, 2, 3, 7, MAX_A};
        a.assign(n, vector<long long>(m, 0));
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                a[i][j] = rnd.any(values);
    } else if (mode == 1) {
        n = rnd.next(2, 10);
        m = rnd.next(2, 8);
        a.assign(n, vector<long long>(m, 0));
        for (int i = 0; i < n; ++i) {
            int nonZero = rnd.next(0, m);
            vector<int> cols(m);
            for (int j = 0; j < m; ++j) cols[j] = j;
            shuffle(cols.begin(), cols.end());
            for (int k = 0; k < nonZero; ++k) a[i][cols[k]] = rnd.next(1LL, 1000LL);
        }
    } else if (mode == 2) {
        n = rnd.next(2, 12);
        m = rnd.next(1, 6);
        a.assign(n, vector<long long>(m, 0));
        vector<long long> sums;
        long long sumCap = min(MAX_A * m, 1048575LL);
        long long xorsum = 0;
        for (int i = 0; i + 1 < n; ++i) {
            long long s = rnd.next(0LL, sumCap);
            sums.push_back(s);
            xorsum ^= s;
        }
        sums.push_back(xorsum);
        for (int i = 0; i < n; ++i) a[i] = splitSum(sums[i], m);
    } else if (mode == 3) {
        n = rnd.next(1, 8);
        m = rnd.next(1, 8);
        a.assign(n, vector<long long>(m, 0));
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                a[i][j] = rnd.next(max(0LL, MAX_A - 10000), MAX_A);
    } else if (mode == 4) {
        n = rnd.next(8, 20);
        m = rnd.next(8, 20);
        a.assign(n, vector<long long>(m, 0));
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                a[i][j] = rnd.next(0LL, 50LL);
    } else {
        n = rnd.next(1, 50);
        m = rnd.next(1, 50);
        a.assign(n, vector<long long>(m, 0));
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                a[i][j] = rnd.next(0LL, MAX_A);
    }

    println(n, m);
    for (const auto& row : a) println(row);

    return 0;
}
