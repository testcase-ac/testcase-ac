#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    int k;

    if (mode == 0) {
        n = rnd.next(5, 9);
        k = rnd.next(1, min(5, n));
    } else if (mode == 1) {
        n = rnd.next(5, 12);
        k = rnd.next(min(3, n), min(8, n));
    } else if (mode == 2) {
        n = rnd.next(8, 18);
        k = rnd.next(2, min(10, n));
    } else if (mode == 3) {
        n = rnd.next(15, 35);
        k = rnd.next(8, min(15, n));
    } else if (mode == 4) {
        n = rnd.next(40, 100);
        k = 15;
    } else {
        n = rnd.next(5, 100);
        k = rnd.next(1, min(15, n));
    }

    vector<int> columns(n);
    for (int i = 0; i < n; ++i) {
        columns[i] = i + 1;
    }

    if (mode == 1 && n >= 2) {
        vector<int> preferred;
        preferred.push_back(1);
        preferred.push_back(n);
        for (int c = 2; c < n; ++c) {
            preferred.push_back(c);
        }
        columns = preferred;
    } else {
        shuffle(columns.begin(), columns.end());
    }

    columns.resize(k);
    shuffle(columns.begin(), columns.end());

    int startColumn;
    if (mode == 1) {
        startColumn = rnd.any(vector<int>{1, n});
    } else if (mode == 2) {
        int center = rnd.next(1, n);
        int span = rnd.next(0, min(3, n - 1));
        startColumn = rnd.next(max(1, center - span), min(n, center + span));
    } else if (mode == 4) {
        startColumn = rnd.any(vector<int>{1, n, rnd.next(1, n)});
    } else {
        startColumn = rnd.next(1, n);
    }

    vector<int> rows;
    rows.reserve(k);
    for (int i = 0; i < k; ++i) {
        int r;
        if (mode == 0) {
            r = rnd.next(max(1, n - 3), n - 1);
        } else if (mode == 2) {
            r = rnd.next(1, min(n - 1, 4));
        } else if (mode == 3) {
            r = rnd.next(1, n - 1);
            if (rnd.next(0, 2) == 0) {
                r = rnd.next(max(1, n - 6), n - 1);
            }
        } else if (mode == 4) {
            r = rnd.any(vector<int>{1, rnd.next(1, n - 1), max(1, n / 2), n - 1});
        } else {
            r = rnd.next(1, n - 1);
        }
        rows.push_back(r);
    }

    println(n, k);
    for (int i = 0; i < k; ++i) {
        println(rows[i], columns[i]);
    }
    println(startColumn);

    return 0;
}
