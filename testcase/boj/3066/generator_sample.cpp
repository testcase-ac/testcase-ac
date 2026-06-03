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

void applyBlockShuffle(vector<int>& p) {
    int n = int(p.size());
    int blockSize = rnd.next(2, max(2, min(n, 6)));
    for (int start = 0; start < n; start += blockSize) {
        int finish = min(n, start + blockSize);
        if (rnd.next(2) == 0) {
            reverse(p.begin() + start, p.begin() + finish);
        } else {
            shuffle(p.begin() + start, p.begin() + finish);
        }
    }
}

void applySawtooth(vector<int>& p) {
    vector<int> odds, evens;
    for (int x : p) {
        if (x % 2 == 1) {
            odds.push_back(x);
        } else {
            evens.push_back(x);
        }
    }
    if (rnd.next(2) == 0) {
        reverse(evens.begin(), evens.end());
    } else {
        reverse(odds.begin(), odds.end());
    }
    p.clear();
    p.insert(p.end(), odds.begin(), odds.end());
    p.insert(p.end(), evens.begin(), evens.end());
}

vector<int> makePermutation(int n, int mode) {
    vector<int> p = identityPermutation(n);

    if (mode == 0) {
        return p;
    }
    if (mode == 1) {
        reverse(p.begin(), p.end());
        return p;
    }
    if (mode == 2) {
        int swaps = rnd.next(1, max(1, n / 2));
        for (int i = 0; i < swaps; ++i) {
            swap(p[rnd.next(n)], p[rnd.next(n)]);
        }
        return p;
    }
    if (mode == 3) {
        applyBlockShuffle(p);
        return p;
    }
    if (mode == 4) {
        applySawtooth(p);
        return p;
    }

    shuffle(p.begin(), p.end());
    return p;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int T = rnd.next(2, 7);
    println(T);

    for (int tc = 0; tc < T; ++tc) {
        int mode = (tc < 6 ? tc : rnd.next(6));
        int n;
        if (tc == 0) {
            n = 1;
        } else if (rnd.next(4) == 0) {
            n = rnd.next(2, 6);
        } else {
            n = rnd.next(7, 24);
        }

        vector<int> p = makePermutation(n, mode);

        println(n);
        for (int x : p) {
            println(x);
        }
    }

    return 0;
}
