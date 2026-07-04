#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

const int MIN_N = 3;
const int MAX_N = 9999999;

int clampN(int n) {
    return max(MIN_N, min(MAX_N, n));
}

void addNear(vector<int>& values, int center, int spread) {
    int count = rnd.next(1, 6);
    for (int i = 0; i < count; ++i) {
        values.push_back(clampN(center + rnd.next(-spread, spread)));
    }
}

int randomPowerOfTwo() {
    int exponent = rnd.next(2, 23);
    return 1 << exponent;
}

void printCases(const vector<int>& values) {
    for (int i = 0; i < static_cast<int>(values.size()); ++i) {
        if (i > 0) {
            if (rnd.next(0, 4) == 0) {
                printf("\n");
            } else {
                printf(" ");
            }
        }
        printf("%d", values[i]);
    }
    printf("\n");
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    vector<int> values;

    if (mode == 0) {
        int caseCount = rnd.next(1, 16);
        for (int i = 0; i < caseCount; ++i) {
            values.push_back(rnd.next(MIN_N, 120));
        }
    } else if (mode == 1) {
        int groups = rnd.next(2, 8);
        for (int i = 0; i < groups; ++i) {
            addNear(values, randomPowerOfTwo(), rnd.next(0, 5));
        }
    } else if (mode == 2) {
        int groups = rnd.next(2, 8);
        for (int i = 0; i < groups; ++i) {
            addNear(values, randomPowerOfTwo() - 1, rnd.next(0, 4));
        }
    } else if (mode == 3) {
        int groups = rnd.next(1, 6);
        for (int i = 0; i < groups; ++i) {
            int center = rnd.any(vector<int>{MIN_N, MIN_N + 1, 7, 15, 31, 63, MAX_N - 1, MAX_N});
            addNear(values, center, rnd.next(0, 3));
        }
    } else if (mode == 4) {
        int caseCount = rnd.next(20, 100);
        for (int i = 0; i < caseCount; ++i) {
            int hi = rnd.next(1000, MAX_N);
            values.push_back(rnd.next(MIN_N, hi));
        }
    } else {
        int caseCount = rnd.next(1, 100);
        for (int i = 0; i < caseCount; ++i) {
            values.push_back(rnd.next(MIN_N, MAX_N));
        }
    }

    shuffle(values.begin(), values.end());
    if (values.size() > 100) {
        values.resize(100);
    }

    printCases(values);
    return 0;
}
