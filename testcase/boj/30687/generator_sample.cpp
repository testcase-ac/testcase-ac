#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    vector<int> a;

    if (mode == 0) {
        n = rnd.next(1, 30);
        a.assign(n, 1);
    } else if (mode == 1) {
        n = rnd.next(2, 25);
        a.assign(n, 1);
        int largeIndex = rnd.next(0, n - 1);
        int targetSum = rnd.next(n, min(500000, n + rnd.next(20, 180)));
        a[largeIndex] += targetSum - n;
    } else if (mode == 2) {
        n = rnd.next(2, 28);
        a.resize(n);
        int base = rnd.next(1, 4);
        int step = rnd.next(0, 5);
        for (int i = 0; i < n; ++i) {
            a[i] = base + step * i + rnd.next(0, 3);
        }
        if (rnd.next(0, 1)) {
            reverse(a.begin(), a.end());
        }
    } else if (mode == 3) {
        n = rnd.next(5, 35);
        a.assign(n, 1);
        int spikes = rnd.next(1, min(5, n));
        vector<int> indices(n);
        iota(indices.begin(), indices.end(), 0);
        shuffle(indices.begin(), indices.end());
        for (int i = 0; i < spikes; ++i) {
            a[indices[i]] += rnd.next(2, 40);
        }
    } else if (mode == 4) {
        n = rnd.next(1, 40);
        a.assign(n, 1);
        int extra = rnd.next(0, 220);
        for (int i = 0; i < extra; ++i) {
            int bias = rnd.next(0, 2);
            int index;
            if (bias == 0) {
                index = rnd.wnext(n, -2);
            } else if (bias == 1) {
                index = rnd.wnext(n, 2);
            } else {
                index = rnd.next(0, n - 1);
            }
            ++a[index];
        }
    } else {
        n = rnd.next(1, 18);
        a.resize(n);
        for (int i = 0; i < n; ++i) {
            a[i] = rnd.next(1, 12);
        }
    }

    println(n);
    println(a);
    return 0;
}
