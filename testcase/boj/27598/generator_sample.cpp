#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

static vector<int> identityPermutation(int n) {
    vector<int> p(n);
    iota(p.begin(), p.end(), 1);
    return p;
}

static vector<int> randomPermutation(int n) {
    vector<int> p = identityPermutation(n);
    shuffle(p.begin(), p.end());
    return p;
}

static vector<int> rotatedPermutation(const vector<int>& a) {
    vector<int> b = a;
    int n = int(b.size());
    if (n > 1) {
        rotate(b.begin(), b.begin() + rnd.next(1, n - 1), b.end());
    }
    return b;
}

static vector<int> swappedBlocksPermutation(const vector<int>& a) {
    int n = int(a.size());
    if (n <= 2) {
        vector<int> b = a;
        reverse(b.begin(), b.end());
        return b;
    }

    int firstLen = rnd.next(1, n / 2);
    int secondLen = rnd.next(1, n - firstLen);
    int firstStart = rnd.next(0, n - firstLen - secondLen);
    int secondStart = rnd.next(firstStart + firstLen, n - secondLen);

    vector<int> b;
    b.insert(b.end(), a.begin(), a.begin() + firstStart);
    b.insert(b.end(), a.begin() + secondStart, a.begin() + secondStart + secondLen);
    b.insert(b.end(), a.begin() + firstStart + firstLen, a.begin() + secondStart);
    b.insert(b.end(), a.begin() + firstStart, a.begin() + firstStart + firstLen);
    b.insert(b.end(), a.begin() + secondStart + secondLen, a.end());
    return b;
}

static vector<int> perturbedPermutation(const vector<int>& a) {
    vector<int> b = a;
    int n = int(b.size());
    int swaps = rnd.next(1, min(n, 4));
    for (int i = 0; i < swaps; ++i) {
        int x = rnd.next(0, n - 1);
        int y = rnd.next(0, n - 1);
        swap(b[x], b[y]);
    }
    return b;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(6, 18);
    vector<pair<vector<int>, vector<int>>> tests;

    for (int tc = 0; tc < t; ++tc) {
        int n;
        if (tc == 0) {
            n = 1;
        } else if (rnd.next(100) < 75) {
            n = rnd.next(2, 12);
        } else {
            n = rnd.next(13, 35);
        }

        vector<int> a = randomPermutation(n);
        vector<int> b;
        int mode = rnd.next(0, 5);
        if (mode == 0) {
            b = a;
        } else if (mode == 1) {
            b = a;
            reverse(b.begin(), b.end());
        } else if (mode == 2) {
            b = rotatedPermutation(a);
        } else if (mode == 3) {
            b = swappedBlocksPermutation(a);
        } else if (mode == 4) {
            b = perturbedPermutation(a);
        } else {
            b = randomPermutation(n);
        }

        tests.push_back({a, b});
    }

    println(int(tests.size()));
    for (const auto& test : tests) {
        println(int(test.first.size()));
        println(test.first);
        println(test.second);
    }

    return 0;
}
