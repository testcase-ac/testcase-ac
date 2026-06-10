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
        int swaps = rnd.next(1, max(1, n / 3));
        for (int i = 0; i < swaps; ++i) {
            int a = rnd.next(0, n - 1);
            int b = rnd.next(max(0, a - 2), min(n - 1, a + 2));
            swap(p[a], p[b]);
        }
        return p;
    }
    if (mode == 3) {
        int cut = rnd.next(0, n - 1);
        rotate(p.begin(), p.begin() + cut, p.end());
        if (rnd.next(0, 1)) {
            reverse(p.begin(), p.begin() + rnd.next(1, n));
        }
        return p;
    }
    if (mode == 4) {
        for (int len = n; len >= 2; --len) {
            if (rnd.next(0, 2) != 0) {
                reverse(p.begin(), p.begin() + rnd.next(2, len));
            }
        }
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
        int sizeMode = rnd.next(0, 4);
        int n;
        if (sizeMode == 0) {
            n = rnd.next(1, 4);
        } else if (sizeMode == 1) {
            n = rnd.next(5, 12);
        } else if (sizeMode == 2) {
            n = rnd.next(13, 30);
        } else if (sizeMode == 3) {
            n = 30;
        } else {
            n = rnd.next(1, 30);
        }

        vector<int> p = makePermutation(n, rnd.next(0, 5));
        cout << n;
        for (int pancake : p) {
            cout << ' ' << pancake;
        }
        cout << '\n';
    }

    return 0;
}
