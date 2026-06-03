#include "testlib.h"
#include <algorithm>
#include <vector>

using namespace std;

vector<int> randomRow(int n) {
    vector<int> row(n);
    for (int i = 0; i < n; ++i) {
        row[i] = rnd.next(0, 1) ? 1 : -1;
    }
    return row;
}

vector<int> blockRow(int n) {
    vector<int> row(n, -1);
    int ones = rnd.next(0, n);
    vector<int> order(n);
    for (int i = 0; i < n; ++i) {
        order[i] = i;
    }
    shuffle(order.begin(), order.end());
    for (int i = 0; i < ones; ++i) {
        row[order[i]] = 1;
    }
    return row;
}

vector<int> mutateRow(vector<int> row) {
    int n = (int)row.size();
    int flips = rnd.next(1, max(1, n / 2));
    vector<int> order(n);
    for (int i = 0; i < n; ++i) {
        order[i] = i;
    }
    shuffle(order.begin(), order.end());
    for (int i = 0; i < flips; ++i) {
        row[order[i]] *= -1;
    }
    return row;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int sizeMode = rnd.next(0, 4);
    int n;
    if (sizeMode == 0) {
        n = 2;
    } else if (sizeMode <= 2) {
        n = 2 * rnd.next(1, 5);
    } else {
        n = 2 * rnd.next(5, 12);
    }

    int m;
    if (sizeMode == 0) {
        m = rnd.next(1, 8);
    } else if (sizeMode <= 2) {
        m = rnd.next(1, 25);
    } else {
        m = rnd.next(20, 80);
    }

    vector<vector<int>> rows;
    vector<int> base = randomRow(n);
    int mode = rnd.next(0, 5);

    for (int i = 0; i < m; ++i) {
        vector<int> row;
        if (mode == 0) {
            row = randomRow(n);
        } else if (mode == 1) {
            row = blockRow(n);
        } else if (mode == 2) {
            row = mutateRow(base);
        } else if (mode == 3) {
            row = (i % 2 == 0 ? base : mutateRow(base));
        } else if (mode == 4) {
            row.assign(n, (i % 2 == 0) ? 1 : -1);
        } else {
            row = randomRow(n);
            if (!rows.empty() && rnd.next(0, 2) == 0) {
                row = rnd.any(rows);
            }
        }
        rows.push_back(row);
    }

    println(n, m);
    for (const vector<int>& row : rows) {
        println(row);
    }

    return 0;
}
