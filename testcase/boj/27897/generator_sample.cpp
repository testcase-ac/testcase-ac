#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(6);
    int n;
    if (mode == 5 && rnd.next(3) == 0) {
        n = rnd.next(50, 120);
    } else {
        n = rnd.next(1, 18);
    }

    vector<int> p(n);
    iota(p.begin(), p.end(), 1);

    if (mode == 1) {
        reverse(p.begin(), p.end());
    } else if (mode == 2) {
        if (n > 1) {
            int swaps = rnd.next(1, 2 * n);
            for (int i = 0; i < swaps; ++i) {
                int pos = rnd.next(0, n - 2);
                swap(p[pos], p[pos + 1]);
            }
        }
    } else if (mode == 3) {
        int block = rnd.next(2, max(2, min(n, 7)));
        for (int l = 0; l < n; l += block) {
            int r = min(n, l + block);
            reverse(p.begin() + l, p.begin() + r);
        }
    } else if (mode == 4) {
        vector<int> q;
        int low = 1;
        int high = n;
        while (low <= high) {
            if (rnd.next(2) == 0) {
                q.push_back(high--);
            } else {
                q.push_back(low++);
            }
        }
        p = q;
    } else if (mode == 5) {
        shuffle(p.begin(), p.end());
    }

    long long maxInversions = 1LL * n * (n - 1) / 2;
    long long l;
    int lMode = rnd.next(5);
    if (lMode == 0) {
        l = 1;
    } else if (lMode == 1) {
        l = rnd.next(1LL, max(1LL, maxInversions));
    } else if (lMode == 2) {
        l = maxInversions + rnd.next(1LL, 1000LL);
    } else if (lMode == 3) {
        l = rnd.next(1000000LL, 1000000000000LL);
    } else {
        l = 1000000000000000000LL;
    }

    println(n, l);
    println(p);

    return 0;
}
