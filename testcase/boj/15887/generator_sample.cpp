#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

static vector<int> identityPermutation(int n) {
    vector<int> p(n);
    for (int i = 0; i < n; ++i) {
        p[i] = i + 1;
    }
    return p;
}

static void applyRandomReverses(vector<int>& p, int operations) {
    int n = static_cast<int>(p.size());
    for (int i = 0; i < operations; ++i) {
        int l = rnd.next(0, n - 2);
        int r = rnd.next(l + 1, n - 1);
        reverse(p.begin() + l, p.begin() + r + 1);
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int sizeMode = rnd.next(100);
    int n;
    if (sizeMode < 55) {
        n = rnd.next(1, 12);
    } else if (sizeMode < 90) {
        n = rnd.next(13, 80);
    } else {
        n = rnd.next(81, 1000);
    }

    vector<int> p = identityPermutation(n);
    int mode = rnd.next(8);

    if (mode == 1) {
        reverse(p.begin(), p.end());
    } else if (mode == 2) {
        shuffle(p.begin(), p.end());
    } else if (mode == 3) {
        int block = rnd.next(2, min(n, 12));
        for (int l = 0; l < n; l += block) {
            int r = min(n, l + block);
            reverse(p.begin() + l, p.begin() + r);
        }
    } else if (mode == 4) {
        int swaps = rnd.next(1, max(1, n / 2));
        for (int i = 0; i < swaps; ++i) {
            int a = rnd.next(0, n - 1);
            int b = rnd.next(0, n - 1);
            swap(p[a], p[b]);
        }
    } else if (mode == 5 && n > 1) {
        int shift = rnd.next(1, n - 1);
        rotate(p.begin(), p.begin() + shift, p.end());
    } else if (mode == 6 && n > 1) {
        int operations = rnd.next(1, min(30, n * 2));
        applyRandomReverses(p, operations);
    } else if (mode == 7 && n > 1) {
        int l = rnd.next(0, n - 2);
        int r = rnd.next(l + 1, n - 1);
        reverse(p.begin() + l, p.begin() + r + 1);
    }

    println(n);
    println(p);
    return 0;
}
