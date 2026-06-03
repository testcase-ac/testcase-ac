#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

static vector<int> makeCombination(int n, int k, int mode) {
    vector<int> values;
    values.reserve(k);

    if (k == 0) {
        return values;
    }

    if (mode == 0) {
        for (int i = 1; i <= k; ++i) {
            values.push_back(i);
        }
    } else if (mode == 1) {
        for (int i = n - k + 1; i <= n; ++i) {
            values.push_back(i);
        }
    } else {
        vector<int> candidates;
        candidates.reserve(n);
        for (int i = 1; i <= n; ++i) {
            candidates.push_back(i);
        }
        shuffle(candidates.begin(), candidates.end());
        candidates.resize(k);
        sort(candidates.begin(), candidates.end());
        values = candidates;
    }

    return values;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(8, 18);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        int n;
        if (tc == 0) {
            n = 1;
        } else if (tc == 1) {
            n = 50;
        } else if (rnd.next(4) == 0) {
            n = rnd.next(40, 50);
        } else {
            n = rnd.next(2, 12);
        }

        int k;
        int shape = rnd.next(6);
        if (shape == 0) {
            k = 0;
        } else if (shape == 1) {
            k = n;
        } else if (shape == 2) {
            k = 1;
        } else if (shape == 3) {
            k = n - 1;
        } else {
            k = rnd.next(0, n);
        }

        int mode = rnd.next(3);
        vector<int> combination = makeCombination(n, k, mode);

        println(n, k);
        if (combination.empty()) {
            printf("\n");
        } else {
            println(combination);
        }
    }

    return 0;
}
