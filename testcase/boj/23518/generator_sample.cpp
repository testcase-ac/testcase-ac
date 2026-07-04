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

static void applyRandomSwaps(vector<int>& p, int swaps) {
    int n = (int)p.size();
    for (int i = 0; i < swaps; ++i) {
        int a = rnd.next(0, n - 1);
        int b = rnd.next(0, n - 1);
        swap(p[a], p[b]);
    }
}

static vector<int> divisorHeavyPermutation(int n) {
    vector<int> p;
    vector<int> used(n + 1, 0);

    for (int base = 1; base <= n; base *= 2) {
        for (int x = base; x <= n; x *= 2) {
            if (!used[x]) {
                p.push_back(x);
                used[x] = 1;
            }
            if (x > n / 2) {
                break;
            }
        }
        if (base > n / 2) {
            break;
        }
    }

    for (int d = 2; d <= min(n, 20); ++d) {
        for (int x = d; x <= n; x += d) {
            if (!used[x]) {
                p.push_back(x);
                used[x] = 1;
            }
        }
    }

    vector<int> rest;
    for (int x = 1; x <= n; ++x) {
        if (!used[x]) {
            rest.push_back(x);
        }
    }
    shuffle(rest.begin(), rest.end());
    p.insert(p.end(), rest.begin(), rest.end());

    return p;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n;
    if (mode == 0) {
        n = 1;
    } else if (mode <= 2) {
        n = rnd.next(2, 12);
    } else if (mode <= 5) {
        n = rnd.next(13, 80);
    } else if (mode == 6) {
        n = rnd.next(200, 1200);
    } else {
        n = rnd.next(90000, 100000);
    }

    vector<int> p = identityPermutation(n);

    if (mode == 1) {
        reverse(p.begin(), p.end());
    } else if (mode == 2) {
        shuffle(p.begin(), p.end());
    } else if (mode == 3) {
        int shift = rnd.next(1, n - 1);
        rotate(p.begin(), p.begin() + shift, p.end());
        applyRandomSwaps(p, rnd.next(1, min(n, 8)));
    } else if (mode == 4) {
        p = divisorHeavyPermutation(n);
        applyRandomSwaps(p, rnd.next(0, min(n, 12)));
    } else if (mode == 5) {
        reverse(p.begin(), p.end());
        applyRandomSwaps(p, rnd.next(1, min(n, 20)));
    } else if (mode == 6) {
        p = divisorHeavyPermutation(n);
        int cut = rnd.next(1, n - 1);
        reverse(p.begin(), p.begin() + cut);
    } else {
        shuffle(p.begin(), p.end());
    }

    println(n);
    println(p);

    return 0;
}
