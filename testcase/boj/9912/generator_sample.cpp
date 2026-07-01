#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n;
    vector<int> p;

    if (mode == 0) {
        n = rnd.next(1, 4);
        p.resize(n);
        iota(p.begin(), p.end(), 0);
        shuffle(p.begin(), p.end());
    } else if (mode == 1) {
        n = rnd.next(5, 13);
        p.resize(n);
        iota(p.begin(), p.end(), 0);
        shuffle(p.begin(), p.end());
    } else if (mode == 2) {
        n = rnd.next(2, 13);
        p.resize(n);
        iota(p.begin(), p.end(), 0);
        int swaps = rnd.next(1, min(n, 4));
        for (int i = 0; i < swaps; ++i) {
            int a = rnd.next(0, n - 1);
            int b = rnd.next(0, n - 1);
            swap(p[a], p[b]);
        }
    } else if (mode == 3) {
        n = rnd.next(2, 13);
        p.resize(n);
        iota(p.begin(), p.end(), 0);
        reverse(p.begin(), p.end());
        int swaps = rnd.next(0, min(n, 3));
        for (int i = 0; i < swaps; ++i) {
            int a = rnd.next(0, n - 1);
            int b = rnd.next(0, n - 1);
            swap(p[a], p[b]);
        }
    } else if (mode == 4) {
        n = rnd.next(3, 13);
        p.resize(n);
        iota(p.begin(), p.end(), 0);
        int shift = rnd.next(1, n - 1);
        rotate(p.begin(), p.begin() + shift, p.end());
        if (rnd.next(0, 1) == 1) {
            reverse(p.begin() + rnd.next(0, n - 2), p.end());
        }
    } else if (mode == 5) {
        n = 13;
        p.resize(n);
        iota(p.begin(), p.end(), 0);
        int prefix = rnd.next(4, 9);
        shuffle(p.begin(), p.begin() + prefix);
    } else {
        n = 13;
        p.resize(n);
        iota(p.begin(), p.end(), 0);
        reverse(p.begin(), p.end());
        int suffixStart = rnd.next(3, 8);
        shuffle(p.begin() + suffixStart, p.end());
    }

    println(n);
    println(p);
    return 0;
}
