#include "testlib.h"

#include <algorithm>
#include <cstdlib>
#include <vector>

using namespace std;

vector<int> splitPositive(int parts, int total) {
    vector<int> values(parts, 1);
    int remaining = total - parts;

    while (remaining > 0) {
        int i = rnd.next(parts);
        int add = rnd.next(1, min(remaining, 99 - values[i]));
        values[i] += add;
        remaining -= add;
    }

    shuffle(values.begin(), values.end());
    return values;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    int n = rnd.next(1, 8);
    int m = rnd.next(1, 8);
    int total = rnd.next(max(n, m), min(100 * min(n, m), 70));

    vector<int> wants = splitPositive(n, total);
    vector<int> stocks = splitPositive(m, total);
    vector<vector<int>> cap(m, vector<int>(n, 0));

    if (mode == 0) {
        for (int i = 0; i < m; ++i)
            for (int j = 0; j < n; ++j)
                cap[i][j] = rnd.next(0, min(100, stocks[i]));
    } else if (mode == 1) {
        for (int i = 0; i < m; ++i)
            for (int j = 0; j < n; ++j)
                cap[i][j] = rnd.next(100) < 70 ? rnd.next(0, 5) : rnd.next(6, 100);
    } else if (mode == 2) {
        for (int i = 0; i < m; ++i) {
            int center = i * n / m;
            for (int j = 0; j < n; ++j) {
                int distance = abs(j - center);
                cap[i][j] = distance <= 1 ? rnd.next(1, 100) : rnd.next(0, 3);
            }
        }
    } else if (mode == 3) {
        for (int i = 0; i < m; ++i)
            for (int j = 0; j < n; ++j)
                cap[i][j] = rnd.next(100) < 35 ? 0 : rnd.next(1, 100);
    } else {
        for (int i = 0; i < m; ++i)
            for (int j = 0; j < n; ++j)
                cap[i][j] = min(100, rnd.next(0, wants[j]));
    }

    println(n, m);
    println(wants);
    println(stocks);
    for (const vector<int>& row : cap) println(row);

    return 0;
}
