#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(2, 18);
    vector<int> b;

    if (mode <= 2) {
        vector<int> a(n);
        int valueMode = rnd.next(0, 3);
        for (int i = 0; i < n; ++i) {
            if (valueMode == 0) {
                a[i] = rnd.next(1, 12);
            } else if (valueMode == 1) {
                a[i] = rnd.any(vector<int>{1, 2, 4, 5, 10, 20, 25, 50, 100});
            } else {
                a[i] = rnd.next(1, 100);
            }
        }

        for (int i = 0; i + 1 < n; ++i) {
            b.push_back(a[i] * a[i + 1]);
        }
    } else if (mode == 3) {
        n = rnd.next(2, 10);
        for (int i = 0; i + 1 < n; ++i) {
            b.push_back(rnd.any(vector<int>{101, 103, 107, 109, 9973}));
        }
    } else if (mode == 4) {
        n = 18;
        for (int i = 0; i + 1 < n; ++i) {
            b.push_back((i % 2 == 0) ? 10000 : rnd.any(vector<int>{1, 2, 100}));
        }
    } else {
        n = rnd.next(2, 18);
        int lo = rnd.next(1, 100);
        int hi = rnd.next(lo, 10000);
        for (int i = 0; i + 1 < n; ++i) {
            b.push_back(rnd.next(lo, hi));
        }
    }

    shuffle(b.begin(), b.end());

    println(n);
    println(b);
    return 0;
}
