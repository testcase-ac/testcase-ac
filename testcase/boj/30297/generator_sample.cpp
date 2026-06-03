#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>
using namespace std;

vector<int> identityPermutation(int n) {
    vector<int> p(n);
    iota(p.begin(), p.end(), 1);
    return p;
}

vector<int> rotatedPermutation(int n) {
    vector<int> p = identityPermutation(n);
    if (n > 1) {
        rotate(p.begin(), p.begin() + rnd.next(1, n - 1), p.end());
    }
    return p;
}

vector<int> blockPermutation(int n) {
    vector<int> p;
    int nextValue = 1;
    while (nextValue <= n) {
        int remaining = n - nextValue + 1;
        int len = min(remaining, rnd.next(1, 5));
        vector<int> block;
        for (int value = nextValue; value < nextValue + len; ++value) {
            block.push_back(value);
        }
        if (len >= 2 && rnd.next(0, 2) != 0) {
            rotate(block.begin(), block.begin() + rnd.next(1, len - 1), block.end());
        } else {
            shuffle(block.begin(), block.end());
        }
        p.insert(p.end(), block.begin(), block.end());
        nextValue += len;
    }
    return p;
}

vector<int> boundarySwapPermutation(int n) {
    vector<int> p = identityPermutation(n);
    if (n == 1) return p;

    int swaps = rnd.next(1, max(1, min(n - 1, 8)));
    for (int i = 0; i < swaps; ++i) {
        int pos = rnd.next(0, n - 2);
        swap(p[pos], p[pos + 1]);
    }
    return p;
}

vector<int> randomPermutation(int n) {
    vector<int> p = identityPermutation(n);
    shuffle(p.begin(), p.end());
    return p;
}

int chooseN(int mode) {
    if (mode == 0) return 1;
    if (mode == 1) return rnd.next(2, 8);
    if (mode == 2) return rnd.next(8, 25);
    return rnd.next(25, 80);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(5, 12);
    vector<vector<int>> tests;
    tests.reserve(t);

    for (int tc = 0; tc < t; ++tc) {
        int sizeMode = (tc == 0 ? 0 : rnd.next(1, 3));
        int n = chooseN(sizeMode);
        int mode = rnd.next(0, 4);

        if (mode == 0) {
            tests.push_back(identityPermutation(n));
        } else if (mode == 1) {
            tests.push_back(rotatedPermutation(n));
        } else if (mode == 2) {
            tests.push_back(blockPermutation(n));
        } else if (mode == 3) {
            tests.push_back(boundarySwapPermutation(n));
        } else {
            tests.push_back(randomPermutation(n));
        }
    }

    println((int)tests.size());
    for (const vector<int>& p : tests) {
        println((int)p.size());
        println(p);
    }

    return 0;
}
