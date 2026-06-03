#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(3, 30);
    vector<int> a(n);

    if (mode == 0) {
        int cur = rnd.next(1, 20);
        for (int i = 0; i < n; ++i) {
            cur += rnd.next(1, 4);
            a[i] = cur;
        }
    } else if (mode == 1) {
        int cur = rnd.next(1, 20);
        for (int i = 0; i < n; ++i) {
            cur += rnd.next(1, 4);
            a[i] = cur;
        }
        rotate(a.begin(), a.begin() + rnd.next(1, n - 1), a.end());
    } else if (mode == 2) {
        int cur = rnd.next(100, 160);
        for (int i = 0; i < n; ++i) {
            cur -= rnd.next(0, 4);
            a[i] = max(1, cur);
        }
    } else if (mode == 3) {
        int low = rnd.next(1, 15);
        int high = low + rnd.next(0, 3);
        for (int i = 0; i < n; ++i) {
            a[i] = rnd.next(low, high);
        }
    } else if (mode == 4) {
        int blocks = rnd.next(2, min(8, n));
        vector<int> values(blocks);
        int cur = rnd.next(1, 25);
        for (int i = 0; i < blocks; ++i) {
            cur += rnd.next(0, 5);
            values[i] = cur;
        }
        int pos = 0;
        for (int b = 0; b < blocks; ++b) {
            int remaining = n - pos;
            int take = (b == blocks - 1) ? remaining : rnd.next(1, remaining - (blocks - b - 1));
            for (int j = 0; j < take; ++j) {
                a[pos++] = values[b];
            }
        }
        rotate(a.begin(), a.begin() + rnd.next(0, n - 1), a.end());
    } else {
        int low = rnd.next(1, 50);
        int high = low + rnd.next(10, 80);
        for (int i = 0; i < n; ++i) {
            a[i] = rnd.next(low, high);
        }
    }

    println(n);
    println(a);

    return 0;
}
