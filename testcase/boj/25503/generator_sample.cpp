#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

static void reverseRandomIntervals(vector<int>& p, int rounds) {
    int n = (int)p.size();
    for (int rep = 0; rep < rounds; ++rep) {
        int l = rnd.next(0, n - 1);
        int r = rnd.next(l, n - 1);
        reverse(p.begin() + l, p.begin() + r + 1);
    }
}

static vector<int> buildByRecursiveBlocks(int lo, int hi) {
    if (lo == hi) {
        return {lo};
    }

    int cut = rnd.next(lo, hi - 1);
    vector<int> left = buildByRecursiveBlocks(lo, cut);
    vector<int> right = buildByRecursiveBlocks(cut + 1, hi);

    if (rnd.next(2) == 0) {
        left.insert(left.end(), right.begin(), right.end());
        return left;
    }
    right.insert(right.end(), left.begin(), left.end());
    return right;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = rnd.next(1, 6);
    } else if (rnd.next(4) == 0) {
        n = rnd.next(20, 60);
    } else {
        n = rnd.next(2, 18);
    }

    vector<int> p(n);
    iota(p.begin(), p.end(), 1);

    if (mode == 0) {
        if (rnd.next(2) == 0) {
            reverse(p.begin(), p.end());
        }
    } else if (mode == 1) {
        p = buildByRecursiveBlocks(1, n);
    } else if (mode == 2) {
        reverseRandomIntervals(p, rnd.next(1, min(n, 8)));
    } else if (mode == 3) {
        int block = rnd.next(1, min(n, 5));
        vector<vector<int>> blocks;
        for (int l = 0; l < n; l += block) {
            int r = min(n, l + block);
            blocks.push_back(vector<int>(p.begin() + l, p.begin() + r));
            if (rnd.next(2) == 0) {
                reverse(blocks.back().begin(), blocks.back().end());
            }
        }
        shuffle(blocks.begin(), blocks.end());
        p.clear();
        for (const auto& values : blocks) {
            p.insert(p.end(), values.begin(), values.end());
        }
    } else if (mode == 4) {
        shuffle(p.begin(), p.end());
        int rounds = rnd.next(0, min(n, 4));
        reverseRandomIntervals(p, rounds);
    } else {
        for (int i = 0; i + 1 < n; i += 2) {
            if (rnd.next(3) != 0) {
                swap(p[i], p[i + 1]);
            }
        }
        reverseRandomIntervals(p, rnd.next(0, min(n, 5)));
    }

    println(n);
    println(p);
    return 0;
}
