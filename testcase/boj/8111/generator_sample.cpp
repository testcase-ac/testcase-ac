#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> candidates;

    int mode = rnd.next(0, 5);
    if (mode == 0) {
        candidates = {1, 2, 5, 10};
        candidates.push_back(rnd.next(1, 20));
        candidates.push_back(rnd.next(21, 100));
    } else if (mode == 1) {
        int x = 1;
        while (x * 2 <= 20000 && rnd.next(0, 1)) x *= 2;
        int y = 1;
        while (y * 5 <= 20000 && rnd.next(0, 1)) y *= 5;
        candidates = {x, y, x * y};
        candidates.push_back(rnd.next(1, 200) * rnd.any(vector<int>{2, 5, 10}));
    } else if (mode == 2) {
        for (int i = 0; i < 9; ++i) {
            int n = rnd.next(1, 10000) * 2 - 1;
            candidates.push_back(n);
        }
    } else if (mode == 3) {
        vector<int> factors = {3, 7, 9, 11, 13, 37, 101, 999};
        for (int i = 0; i < 9; ++i) {
            int f = rnd.any(factors);
            candidates.push_back(f * rnd.next(1, 20000 / f));
        }
    } else if (mode == 4) {
        for (int i = 0; i < 9; ++i) candidates.push_back(rnd.next(19800, 20000));
    } else {
        for (int i = 0; i < 9; ++i) candidates.push_back(rnd.next(1, 20000));
    }

    for (int& n : candidates) n = max(1, min(20000, n));
    shuffle(candidates.begin(), candidates.end());

    int t = rnd.next(1, min(9, int(candidates.size())));
    println(t);
    for (int i = 0; i < t; ++i) println(candidates[i]);

    return 0;
}
