#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 30);
    vector<int> a(n, 0);

    if (mode == 0) {
        n = rnd.next(1, 30);
        a.assign(n, 0);
    } else if (mode == 1) {
        n = rnd.next(2, 30);
        a.assign(n, 0);
        int fixedCount = rnd.next(1, n);
        for (int i = 0; i < fixedCount; ++i) {
            a[rnd.next(0, n - 1)] = 1;
        }
    } else if (mode == 2) {
        n = rnd.next(1, 30);
        a.assign(n, 0);
        int maxColor = rnd.next(1, 3);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 99) < 55) {
                a[i] = rnd.next(1, maxColor);
            }
        }
    } else if (mode == 3) {
        n = rnd.next(2, 30);
        a.assign(n, 0);
        int pos = rnd.next(0, n - 2);
        int color = rnd.next(1, 3);
        a[pos] = color;
        a[pos + 1] = color;
        for (int i = 0; i < n; ++i) {
            if (a[i] == 0 && rnd.next(0, 99) < 25) {
                a[i] = rnd.next(1, 3);
            }
        }
    } else if (mode == 4) {
        n = rnd.next(3, 30);
        a.assign(n, 0);
        int left = rnd.next(0, n - 2);
        int right = rnd.next(left + 1, n - 1);
        int c1 = rnd.next(1, 3);
        int c2 = rnd.next(1, 3);
        a[left] = c1;
        a[right] = c2;
        for (int i = 0; i < n; ++i) {
            if (a[i] == 0 && rnd.next(0, 99) < 15) {
                a[i] = rnd.next(1, 3);
            }
        }
    } else {
        n = rnd.next(1, 30);
        a.assign(n, 0);
        int phase = rnd.next(1, 3);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 99) < 75) {
                a[i] = (i + phase) % 3 + 1;
            }
        }
    }

    println(n);
    println(a);
    return 0;
}
