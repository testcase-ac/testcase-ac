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

static void moveOwnGift(vector<int>& p, int own, int targetPos) {
    auto it = find(p.begin(), p.end(), own);
    int value = *it;
    p.erase(it);
    p.insert(p.begin() + targetPos, value);
}

static vector<int> blockPermutation(int n, int cow, int blockSize) {
    vector<int> p;
    int blockStart = ((cow - 1) / blockSize) * blockSize + 1;
    int blockEnd = min(n, blockStart + blockSize - 1);

    for (int x = blockStart; x <= blockEnd; ++x) {
        p.push_back(x);
    }
    shuffle(p.begin(), p.end());

    vector<int> rest;
    for (int x = 1; x <= n; ++x) {
        if (x < blockStart || x > blockEnd) {
            rest.push_back(x);
        }
    }
    shuffle(rest.begin(), rest.end());
    p.insert(p.end(), rest.begin(), rest.end());
    return p;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = rnd.next(1, 3);
    } else if (mode == 5) {
        n = rnd.next(18, 35);
    } else {
        n = rnd.next(4, 14);
    }

    vector<vector<int>> prefs(n + 1);
    int blockSize = n == 1 ? 1 : rnd.next(2, min(n, 6));

    for (int cow = 1; cow <= n; ++cow) {
        vector<int> p = identityPermutation(n);

        if (mode == 0) {
            shuffle(p.begin(), p.end());
        } else if (mode == 1) {
            int swaps = rnd.next(0, max(1, n / 2));
            for (int k = 0; k < swaps; ++k) {
                swap(p[rnd.next(n)], p[rnd.next(n)]);
            }
            if (rnd.next(0, 1)) {
                moveOwnGift(p, cow, rnd.next(0, min(n - 1, 3)));
            }
        } else if (mode == 2) {
            reverse(p.begin(), p.end());
            int rotations = rnd.next(0, n - 1);
            rotate(p.begin(), p.begin() + rotations, p.end());
        } else if (mode == 3) {
            p = blockPermutation(n, cow, blockSize);
            if (rnd.next(0, 2) == 0) {
                moveOwnGift(p, cow, rnd.next(0, min(n - 1, blockSize)));
            }
        } else if (mode == 4) {
            int shift = rnd.next(0, n - 1);
            rotate(p.begin(), p.begin() + ((cow - 1 + shift) % n), p.end());
            if (rnd.next(0, 1)) {
                int tailStart = rnd.next(0, n - 1);
                shuffle(p.begin() + tailStart, p.end());
            }
        } else {
            shuffle(p.begin(), p.end());
            int ownPos = rnd.next(0, n - 1);
            moveOwnGift(p, cow, ownPos);
        }

        prefs[cow] = p;
    }

    println(n);
    for (int cow = 1; cow <= n; ++cow) {
        println(prefs[cow]);
    }

    return 0;
}
