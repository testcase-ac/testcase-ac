#include "testlib.h"

#include <algorithm>
#include <set>
#include <vector>

using namespace std;

vector<int> makeValues(int n, bool wideValues) {
    set<int> used;
    vector<int> values;
    values.reserve(n);

    while (static_cast<int>(values.size()) < n) {
        int value;
        if (wideValues) {
            value = rnd.next(0, 999999999);
        } else {
            value = rnd.next(0, max(20, n * 6));
        }
        if (used.insert(value).second) {
            values.push_back(value);
        }
    }

    sort(values.begin(), values.end());
    return values;
}

vector<int> buildCase(int n, int mode) {
    vector<int> values = makeValues(n, mode == 4);

    if (n == 1 || mode == 0) {
        return values;
    }

    if (mode == 1) {
        reverse(values.begin(), values.end());
        return values;
    }

    if (mode == 2) {
        int swaps = rnd.next(1, max(1, n / 2));
        for (int i = 0; i < swaps; ++i) {
            int pos = rnd.next(0, n - 2);
            swap(values[pos], values[pos + 1]);
        }
        return values;
    }

    if (mode == 3) {
        int blockSize = rnd.next(2, min(n, 5));
        for (int start = 0; start < n; start += blockSize) {
            int finish = min(n, start + blockSize);
            reverse(values.begin() + start, values.begin() + finish);
        }
        if (rnd.next(0, 1) == 1) {
            reverse(values.begin(), values.end());
        }
        return values;
    }

    shuffle(values.begin(), values.end());
    return values;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int caseCount = rnd.next(2, 6);
    for (int caseIndex = 0; caseIndex < caseCount; ++caseIndex) {
        int n;
        if (caseIndex == 0 && rnd.next(0, 4) == 0) {
            n = 1;
        } else {
            n = rnd.next(2, 30);
        }

        int mode = rnd.next(0, 4);
        vector<int> values = buildCase(n, mode);

        println(n);
        for (int value : values) {
            println(value);
        }
    }

    println(0);
    return 0;
}
