#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

void buildUniqueNumbers(vector<int>& values, int current, int depth, int maxDepth, vector<bool>& used) {
    if (depth > 0) values.push_back(current);
    if (depth == maxDepth) return;

    vector<int> digits;
    for (int d = 1; d <= 9; ++d) {
        if (!used[d]) digits.push_back(d);
    }
    shuffle(digits.begin(), digits.end());

    for (int d : digits) {
        used[d] = true;
        buildUniqueNumbers(values, current * 10 + d, depth + 1, maxDepth, used);
        used[d] = false;
    }
}

int repeatedDigitNumber(int digits) {
    int d = rnd.next(1, 9);
    int value = 0;
    for (int i = 0; i < digits; ++i) value = value * 10 + d;
    return value;
}

int numberWithZero(int digits) {
    int value = rnd.next(1, 9);
    int zeroPos = rnd.next(1, digits - 1);
    for (int pos = 1; pos < digits; ++pos) {
        int d = (pos == zeroPos) ? 0 : rnd.next(1, 9);
        value = value * 10 + d;
    }
    return value;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> uniqueNumbers;
    vector<bool> used(10, false);
    buildUniqueNumbers(uniqueNumbers, 0, 0, 9, used);
    sort(uniqueNumbers.begin(), uniqueNumbers.end());

    int mode = rnd.next(0, 5);
    int caseCount = rnd.next(6, 24);
    vector<int> cases;

    if (mode == 0) {
        for (int i = 0; i < caseCount; ++i) cases.push_back(rnd.next(0, 200));
    } else if (mode == 1) {
        for (int i = 0; i < caseCount; ++i) {
            int x = rnd.any(uniqueNumbers);
            int offset = rnd.next(-3, 3);
            cases.push_back(max(0, min(999999999, x + offset)));
        }
    } else if (mode == 2) {
        for (int i = 0; i < caseCount; ++i) {
            int digits = rnd.next(2, 9);
            if (rnd.next(0, 1) == 0) {
                cases.push_back(repeatedDigitNumber(digits));
            } else {
                cases.push_back(numberWithZero(digits));
            }
        }
    } else if (mode == 3) {
        int centerIndex = rnd.next(0, (int)uniqueNumbers.size() - 1);
        int lo = max(0, centerIndex - rnd.next(0, 8));
        int hi = min((int)uniqueNumbers.size() - 1, centerIndex + rnd.next(0, 8));
        for (int i = 0; i < caseCount; ++i) {
            int x = uniqueNumbers[rnd.next(lo, hi)];
            cases.push_back(max(0, min(999999999, x + rnd.next(-1, 1))));
        }
    } else if (mode == 4) {
        for (int i = 0; i < caseCount; ++i) {
            int tail = rnd.next(0, 2000000);
            cases.push_back(999999999 - tail);
        }
    } else {
        for (int i = 0; i < caseCount; ++i) cases.push_back(rnd.next(0, 999999999));
    }

    cases.push_back(0);
    cases.push_back(999999999);
    shuffle(cases.begin(), cases.end());

    for (int value : cases) println(value);

    return 0;
}
