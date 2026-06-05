#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

vector<int> maskToRow(int mask) {
    vector<int> row(5);
    for (int j = 0; j < 5; ++j) {
        row[j] = (mask >> (4 - j)) & 1;
    }
    return row;
}

int randomMaskWithProbability(double p) {
    int mask = 0;
    for (int j = 0; j < 5; ++j) {
        if (rnd.next() < p) {
            mask |= 1 << j;
        }
    }
    return mask;
}

int maskContainingPair(int a, int b, double extraProbability) {
    int mask = (1 << a) | (1 << b);
    for (int j = 0; j < 5; ++j) {
        if (j != a && j != b && rnd.next() < extraProbability) {
            mask |= 1 << j;
        }
    }
    return mask;
}

void printRows(const vector<int>& rows) {
    println(static_cast<int>(rows.size()));
    for (int mask : rows) {
        println(maskToRow(mask));
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 30);
    if (rnd.next(0, 9) == 0) {
        n = rnd.next(31, 120);
    }

    vector<int> rows;
    rows.reserve(n);

    if (mode == 0) {
        vector<int> simple = {0, 31, 1, 2, 4, 8, 16};
        for (int i = 0; i < n; ++i) {
            rows.push_back(rnd.any(simple));
        }
    } else if (mode == 1) {
        double p = rnd.next(0.05, 0.35);
        for (int i = 0; i < n; ++i) {
            rows.push_back(randomMaskWithProbability(p));
        }
    } else if (mode == 2) {
        double p = rnd.next(0.65, 0.95);
        for (int i = 0; i < n; ++i) {
            rows.push_back(randomMaskWithProbability(p));
        }
    } else if (mode == 3) {
        int first = rnd.next(0, 4);
        int second = rnd.next(0, 3);
        if (second >= first) {
            ++second;
        }
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 99) < 70) {
                rows.push_back(maskContainingPair(first, second, rnd.next(0.0, 0.5)));
            } else {
                rows.push_back(randomMaskWithProbability(rnd.next(0.2, 0.8)));
            }
        }
    } else if (mode == 4) {
        vector<int> pairMasks;
        for (int a = 0; a < 5; ++a) {
            for (int b = a + 1; b < 5; ++b) {
                pairMasks.push_back((1 << a) | (1 << b));
            }
        }
        for (int i = 0; i < n; ++i) {
            rows.push_back(rnd.any(pairMasks));
        }
    } else {
        vector<int> masks;
        for (int mask = 0; mask < 32; ++mask) {
            masks.push_back(mask);
        }
        shuffle(masks.begin(), masks.end());
        for (int i = 0; i < n; ++i) {
            rows.push_back(masks[i % static_cast<int>(masks.size())]);
        }
    }

    shuffle(rows.begin(), rows.end());
    printRows(rows);
    return 0;
}
