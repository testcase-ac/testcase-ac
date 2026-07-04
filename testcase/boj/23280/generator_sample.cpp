#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

// Generates valid press sequences for the fixed 12-cell game board.
int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode <= 3) {
        n = rnd.next(1, 30);
    } else if (mode == 4) {
        n = rnd.next(31, 300);
    } else {
        n = rnd.next(9000, 10000);
    }

    int a = rnd.next(1, 100);
    int b = rnd.next(1, 100);
    if (rnd.next(0, 4) == 0) {
        a = b;
    } else if (rnd.next(0, 4) == 0) {
        a = rnd.any(vector<int>{1, 100});
        b = rnd.any(vector<int>{1, 100});
    }

    vector<int> seq;
    seq.reserve(n);

    if (mode == 0) {
        int value = rnd.next(1, 12);
        seq.assign(n, value);
    } else if (mode == 1) {
        vector<int> pattern;
        int patternSize = rnd.next(2, 5);
        for (int i = 0; i < patternSize; ++i) {
            pattern.push_back(rnd.next(1, 12));
        }
        for (int i = 0; i < n; ++i) {
            seq.push_back(pattern[i % patternSize]);
        }
    } else if (mode == 2) {
        int cur = rnd.any(vector<int>{1, 3});
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 3) == 0) {
                cur = rnd.next(1, 12);
            } else {
                cur = max(1, min(12, cur + rnd.any(vector<int>{-3, -1, 1, 3})));
            }
            seq.push_back(cur);
        }
    } else if (mode == 3) {
        vector<int> labels;
        for (int x = 1; x <= 12; ++x) {
            labels.push_back(x);
        }
        shuffle(labels.begin(), labels.end());
        for (int i = 0; i < n; ++i) {
            seq.push_back(labels[i % labels.size()]);
        }
    } else {
        for (int i = 0; i < n; ++i) {
            seq.push_back(rnd.next(1, 12));
        }
    }

    println(n, a, b);
    println(seq);
    return 0;
}
