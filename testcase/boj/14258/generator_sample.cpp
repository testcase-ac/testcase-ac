#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = 1;
    int m = 1;

    if (mode == 0) {
        n = 1;
        m = rnd.next(1, 12);
    } else if (mode == 1) {
        n = rnd.next(1, 12);
        m = 1;
    } else if (mode == 2) {
        n = rnd.next(2, 4);
        m = rnd.next(2, 4);
    } else if (mode == 3) {
        n = rnd.next(3, 6);
        m = rnd.next(2, 5);
    } else if (mode == 4) {
        n = rnd.next(2, 5);
        m = rnd.next(3, 6);
    } else {
        n = rnd.next(5, 10);
        m = rnd.next(5, 10);
    }

    int total = n * m;
    vector<int> values;

    int valueMode = rnd.next(0, 4);
    if (valueMode == 0 && total <= 21) {
        values.resize(total);
        iota(values.begin(), values.end(), 0);
    } else if (valueMode == 1) {
        int start = rnd.next(0, 1000000 - total + 1);
        for (int i = 0; i < total; ++i) {
            values.push_back(start + i);
        }
    } else if (valueMode == 2) {
        int base = rnd.next(0, 1000000);
        for (int bit = 0; bit < 20 && (int)values.size() < total; ++bit) {
            int candidate = base ^ (1 << bit);
            if (candidate <= 1000000) {
                values.push_back(candidate);
            }
        }
        while ((int)values.size() < total) {
            values.push_back(rnd.next(0, 1000000));
        }
        sort(values.begin(), values.end());
        values.erase(unique(values.begin(), values.end()), values.end());
        while ((int)values.size() < total) {
            int candidate = rnd.next(0, 1000000);
            if (!binary_search(values.begin(), values.end(), candidate)) {
                values.insert(lower_bound(values.begin(), values.end(), candidate), candidate);
            }
        }
    } else {
        vector<int> pool(1000001);
        iota(pool.begin(), pool.end(), 0);
        shuffle(pool.begin(), pool.end());
        values.assign(pool.begin(), pool.begin() + total);
    }

    shuffle(values.begin(), values.end());

    if (mode == 3) {
        sort(values.begin(), values.end());
    } else if (mode == 4) {
        sort(values.rbegin(), values.rend());
    }

    println(n, m);
    for (int i = 0; i < n; ++i) {
        vector<int> row;
        for (int j = 0; j < m; ++j) {
            row.push_back(values[i * m + j]);
        }
        if (mode == 5 && i % 2 == 1) {
            reverse(row.begin(), row.end());
        }
        println(row);
    }

    return 0;
}
