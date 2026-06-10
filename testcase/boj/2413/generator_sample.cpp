#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

int chooseN() {
    int bucket = rnd.next(100);
    if (bucket < 70) {
        return rnd.next(3, 20);
    }
    if (bucket < 95) {
        return rnd.next(21, 80);
    }
    return rnd.next(81, 200);
}

vector<int> makeIdentityPermutation(int n) {
    vector<int> p(n);
    iota(p.begin(), p.end(), 1);
    return p;
}

void randomAdjacentSwaps(vector<int>& p) {
    int n = (int)p.size();
    double swapProb = rnd.next(0.15, 0.9);
    for (int i = 0; i + 1 < n; ++i) {
        if (rnd.next() < swapProb) {
            swap(p[i], p[i + 1]);
            ++i;
        }
    }
}

void reverseRandomBlocks(vector<int>& p) {
    int n = (int)p.size();
    int blockLimit = rnd.next(2, min(n, 8));
    for (int start = 0; start < n; start += blockLimit) {
        int len = rnd.next(1, min(blockLimit, n - start));
        reverse(p.begin() + start, p.begin() + start + len);
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = chooseN();
    int mode = rnd.next(7);
    vector<int> p = makeIdentityPermutation(n);

    if (mode == 0) {
        randomAdjacentSwaps(p);
    } else if (mode == 1) {
        reverse(p.begin(), p.end());
        randomAdjacentSwaps(p);
    } else if (mode == 2) {
        shuffle(p.begin(), p.end());
    } else if (mode == 3) {
        reverseRandomBlocks(p);
        randomAdjacentSwaps(p);
    } else if (mode == 4) {
        vector<int> q;
        int lo = 1, hi = n;
        bool takeHigh = rnd.next(2);
        while (lo <= hi) {
            if (takeHigh) {
                q.push_back(hi--);
            } else {
                q.push_back(lo++);
            }
            takeHigh = !takeHigh;
        }
        p = q;
    } else if (mode == 5) {
        int rotations = rnd.next(1, n - 1);
        rotate(p.begin(), p.begin() + rotations, p.end());
        randomAdjacentSwaps(p);
    } else {
        int swaps = rnd.next(1, min(n, 12));
        for (int i = 0; i < swaps; ++i) {
            swap(p[rnd.next(n)], p[rnd.next(n)]);
        }
    }

    println(n);
    println(p);

    return 0;
}
