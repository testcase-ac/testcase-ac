#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> candidates;

    int targetCount = rnd.next(4, 24);
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        candidates = {1, 2, 3, 5, 9, 10, 11, 19, 37, 99, 101, 199, 200};
    } else if (mode == 1) {
        int step = rnd.any(vector<int>{2, 4, 5, 10, 20, 25});
        for (int n = step; n <= 200; n += step) {
            candidates.push_back(n);
        }
    } else if (mode == 2) {
        int base = rnd.next(2, 20);
        for (int mul = 1; base * mul <= 200; ++mul) {
            candidates.push_back(base * mul);
        }
    } else if (mode == 3) {
        candidates = {7, 13, 17, 19, 23, 29, 31, 41, 73, 97, 109, 127, 149, 181, 191, 199};
    } else if (mode == 4) {
        int lo = rnd.next(1, 160);
        int hi = rnd.next(lo, 200);
        for (int n = lo; n <= hi; ++n) {
            candidates.push_back(n);
        }
    }

    while ((int)candidates.size() < targetCount) {
        candidates.push_back(rnd.next(1, 200));
    }

    candidates.push_back(1);
    candidates.push_back(200);
    shuffle(candidates.begin(), candidates.end());

    vector<int> tests;
    for (int n : candidates) {
        if (find(tests.begin(), tests.end(), n) == tests.end()) {
            tests.push_back(n);
        }
        if ((int)tests.size() == targetCount) {
            break;
        }
    }

    for (int n : tests) {
        println(n);
    }
    println(0);

    return 0;
}
