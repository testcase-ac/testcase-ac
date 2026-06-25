#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

const long long MAX_H = 1000000000LL;

long long edgeHeight() {
    return rnd.any(vector<long long>{0LL, 1LL, 2LL, MAX_H - 1, MAX_H});
}

long long randomHeight(int mode) {
    if (mode == 0) return rnd.next(0LL, 9LL);
    if (mode == 1) return rnd.next(0LL, 1000LL);
    if (mode == 2) return edgeHeight();
    return rnd.next(0LL, MAX_H);
}

void printCase(const vector<vector<long long>>& h, int k) {
    int r = static_cast<int>(h.size());
    int c = static_cast<int>(h[0].size());
    println(r, c, k);
    for (const auto& row : h) {
        println(row);
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int r = 1;
    int c = 1;

    if (mode == 0) {
        r = 1;
        c = rnd.next(1, 12);
    } else if (mode == 1) {
        r = rnd.next(2, 14);
        c = 1;
    } else if (mode == 6) {
        r = rnd.next(15, 35);
        c = rnd.next(8, 20);
    } else {
        r = rnd.next(2, 10);
        c = rnd.next(2, 10);
    }

    int kMode = rnd.next(0, 4);
    int k = 0;
    if (kMode == 0) {
        k = 0;
    } else if (kMode == 1) {
        k = r - 1;
    } else if (kMode == 2) {
        k = rnd.next(0, r - 1);
    } else {
        k = rnd.next(0, min(r - 1, 3));
    }

    vector<vector<long long>> h(r, vector<long long>(c));

    if (mode == 0 || mode == 1) {
        int valueMode = rnd.next(0, 2);
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                h[i][j] = randomHeight(valueMode);
            }
        }
    } else if (mode == 2) {
        long long high = rnd.next(5LL, 100LL);
        long long low = rnd.next(0LL, high - 1);
        for (int i = 0; i < r; ++i) {
            long long rowValue = (i % 2 == 0 ? high : low);
            for (int j = 0; j < c; ++j) h[i][j] = rowValue;
        }
        int gaps = rnd.next(0, min(c, 3));
        for (int g = 0; g < gaps; ++g) {
            int col = rnd.next(0, c - 1);
            for (int i = 0; i < r; ++i) h[i][col] = high;
        }
    } else if (mode == 3) {
        long long low = rnd.next(0LL, 20LL);
        long long high = rnd.next(low + 1, low + 1000);
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) h[i][j] = low;
        }
        int col = rnd.next(0, c - 1);
        for (int i = r - 1; i >= 0; --i) {
            h[i][col] = high;
            if (c > 1 && rnd.next(0, 2) == 0) {
                col = max(0, min(c - 1, col + rnd.any(vector<int>{-1, 1})));
                h[i][col] = high;
            }
        }
        int blockers = rnd.next(0, min(r, 3));
        for (int b = 0; b < blockers; ++b) {
            h[rnd.next(0, r - 1)][rnd.next(0, c - 1)] = low;
        }
    } else if (mode == 4) {
        long long a = rnd.next(0LL, 50LL);
        long long b = rnd.next(a, a + 50);
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                h[i][j] = ((i + j) % 2 == 0 ? a : b);
                if (rnd.next(0, 4) == 0) h[i][j] = randomHeight(1);
            }
        }
    } else if (mode == 5) {
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                h[i][j] = edgeHeight();
            }
        }
    } else {
        long long base = rnd.next(0LL, MAX_H - r * c - 1LL);
        vector<long long> values;
        values.reserve(r * c);
        for (int i = 0; i < r * c; ++i) values.push_back(base + i);
        shuffle(values.begin(), values.end());
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                h[i][j] = values[i * c + j];
            }
        }
    }

    printCase(h, k);
    return 0;
}
