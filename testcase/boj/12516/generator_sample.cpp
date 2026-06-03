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
            int a = rnd.next(0, n - 1);
            int b = rnd.next(0, n - 1);
            swap(p[a], p[b]);
        }
        return p;
    }

    if (mode == 3) {
        for (int i = 0; i + 1 < n; i += 2) {
            if (rnd.next(2) == 0) {
                swap(p[i], p[i + 1]);
            }
        }
        return p;
    }

    if (mode == 4) {
        int shift = rnd.next(1, n - 1);
        rotate(p.begin(), p.begin() + shift, p.end());
        return p;
    }

    shuffle(p.begin(), p.end());
    return p;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 12);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        int sizeMode = rnd.next(10);
        int n;
        if (sizeMode < 6) {
            n = rnd.next(1, 12);
        } else if (sizeMode < 9) {
            n = rnd.next(13, 50);
        } else {
            n = rnd.next(200, 1000);
        }

        int mode = (n == 1) ? 0 : rnd.next(0, 5);
        vector<int> p = makePermutation(n, mode);

        println(n);
        println(p);
    }

    return 0;
}
