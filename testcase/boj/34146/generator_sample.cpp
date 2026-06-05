#include "testlib.h"
#include <vector>

using namespace std;

int nextValue(bool preferBoundary) {
    if (preferBoundary && rnd.next(4) == 0) {
        return rnd.any(vector<int>{1, 2, 9999, 10000});
    }
    return rnd.next(1, 10000);
}

int nextPairValue(bool preferBoundary) {
    if (preferBoundary && rnd.next(4) == 0) {
        return rnd.any(vector<int>{9999, 10000});
    }
    return rnd.next(100, 9998);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(6);
    int n = rnd.next(1, 8);
    int m = rnd.next(1, 10);

    if (mode == 0) {
        m = 1;
    } else if (mode == 1 || mode == 2) {
        if (m % 2 == 1) {
            ++m;
        }
    } else if (mode == 5) {
        m = rnd.next(3, 9);
        if (m % 2 == 0) {
            ++m;
        }
    } else {
        if (m % 2 == 0) {
            ++m;
        }
    }

    int total = n * m;
    vector<int> cells;
    bool preferBoundary = rnd.next(2) == 0;

    if (mode == 2) {
        for (int i = 0; i + 1 < total; i += 2) {
            int value = nextPairValue(preferBoundary);
            cells.push_back(value);
            cells.push_back(value);
        }
        if ((int)cells.size() < total) {
            cells.push_back(nextValue(preferBoundary));
        }
    } else if (mode == 4) {
        int oddCount = rnd.next(0, n);
        for (int i = 0; i < oddCount; ++i) {
            cells.push_back(nextValue(preferBoundary));
        }
        while ((int)cells.size() + 1 < total) {
            int value = nextPairValue(preferBoundary);
            cells.push_back(value);
            cells.push_back(value);
        }
    } else if (mode == 1 || mode == 5) {
        int oddCount = (mode == 1 ? 2 : n + 1);
        oddCount = min(oddCount, total);
        for (int i = 0; i < oddCount; ++i) {
            cells.push_back(i + 1);
        }
        while ((int)cells.size() + 1 < total) {
            int value = nextPairValue(preferBoundary);
            cells.push_back(value);
            cells.push_back(value);
        }
    } else {
        while ((int)cells.size() < total) {
            cells.push_back(nextValue(preferBoundary));
        }
    }

    while ((int)cells.size() < total) {
        cells.push_back(nextValue(preferBoundary));
    }
    cells.resize(total);
    shuffle(cells.begin(), cells.end());

    println(n, m);
    for (int r = 0; r < n; ++r) {
        vector<int> row;
        for (int c = 0; c < m; ++c) {
            row.push_back(cells[r * m + c]);
        }
        println(row);
    }

    return 0;
}
