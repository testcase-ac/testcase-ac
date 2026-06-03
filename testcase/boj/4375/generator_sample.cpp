#include "testlib.h"

#include <vector>
using namespace std;

bool isValidN(int n) {
    return 1 <= n && n <= 10000 && n % 2 != 0 && n % 5 != 0;
}

int randomValidN(int lo, int hi) {
    int n;
    do {
        n = rnd.next(lo, hi);
    } while (!isValidN(n));
    return n;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> values;
    int mode = rnd.next(0, 4);

    if (mode == 0) {
        values.push_back(rnd.any(vector<int>{1, 3, 7, 9, 11, 37, 101, 9901, 9999}));
    } else if (mode == 1) {
        int caseCount = rnd.next(2, 12);
        for (int i = 0; i < caseCount; ++i) {
            values.push_back(randomValidN(1, 99));
        }
    } else if (mode == 2) {
        int caseCount = rnd.next(3, 20);
        for (int i = 0; i < caseCount; ++i) {
            values.push_back(randomValidN(100, 10000));
        }
    } else if (mode == 3) {
        vector<int> candidates = {3, 7, 9, 11, 13, 27, 37, 81, 101, 333, 999, 9901, 9999};
        shuffle(candidates.begin(), candidates.end());
        int caseCount = rnd.next(2, 8);
        for (int i = 0; i < caseCount; ++i) {
            values.push_back(candidates[i]);
        }
    } else {
        int caseCount = rnd.next(5, 30);
        for (int i = 0; i < caseCount; ++i) {
            if (rnd.next(0, 3) == 0) {
                values.push_back(rnd.any(vector<int>{1, 3, 7, 9901, 9999}));
            } else {
                values.push_back(randomValidN(1, 10000));
            }
        }
    }

    for (int n : values) {
        println(n);
    }

    return 0;
}
