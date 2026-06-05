#include "testlib.h"
#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n = rnd.next(1, 24);
    vector<long long> w(n);

    if (mode == 0) {
        long long value = rnd.any(vector<long long>{0LL, 1LL, 2LL, 1000000000LL});
        fill(w.begin(), w.end(), value);
    } else if (mode == 1) {
        int cap = rnd.next(0, max(0, n - 1));
        for (int i = 0; i < n; ++i) {
            w[i] = rnd.next(0, cap);
        }
    } else if (mode == 2) {
        for (int i = 0; i < n; ++i) {
            w[i] = rnd.next(0, n + 3);
        }
        sort(w.begin(), w.end());
    } else if (mode == 3) {
        for (int i = 0; i < n; ++i) {
            w[i] = rnd.next(0, n + 3);
        }
        sort(w.rbegin(), w.rend());
    } else if (mode == 4) {
        for (int i = 0; i < n; ++i) {
            w[i] = (rnd.next(0, 3) == 0) ? 1000000000LL : rnd.next(0, min(n + 5, 30));
        }
    } else if (mode == 5) {
        int pivot = rnd.next(0, max(0, n - 1));
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 1) == 0) {
                w[i] = max(0, pivot - rnd.next(0, min(pivot, 3)));
            } else {
                w[i] = pivot + rnd.next(0, 3);
            }
        }
    } else {
        for (int i = 0; i < n; ++i) {
            w[i] = rnd.next(0, 1) ? rnd.next(0, 3) : rnd.next(0, 1000000000);
        }
    }

    if (mode != 2 && mode != 3) {
        shuffle(w.begin(), w.end());
    }

    println(n);
    println(w);

    return 0;
}
