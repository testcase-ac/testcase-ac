#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    int k;
    vector<int> a;

    if (mode == 0) {
        n = 2;
        k = 2;
        a = {rnd.next(0, 1000), rnd.next(0, 1000)};
    } else if (mode == 1) {
        n = rnd.next(3, 8);
        k = 2;
        a.resize(n);
        for (int i = 0; i < n; ++i) {
            a[i] = rnd.next(0, 20);
        }
    } else if (mode == 2) {
        n = rnd.next(4, 12);
        k = rnd.next(3, n);
        a.resize(n);
        for (int i = 0; i < n; ++i) {
            a[i] = (i % 2 == 0) ? rnd.next(0, 5) : rnd.next(995, 1000);
        }
    } else if (mode == 3) {
        n = rnd.next(5, 16);
        k = rnd.next(2, n);
        int base = rnd.next(0, 1000);
        a.assign(n, base);
        int changes = rnd.next(1, n);
        for (int i = 0; i < changes; ++i) {
            a[rnd.next(0, n - 1)] = rnd.next(0, 1000);
        }
    } else if (mode == 4) {
        n = rnd.next(6, 18);
        k = rnd.next(max(2, n - 3), n);
        a.resize(n);
        int parity = rnd.next(0, 1);
        for (int i = 0; i < n; ++i) {
            int value = rnd.next(0, 500) * 2 + parity;
            if (value > 1000) value -= 2;
            a[i] = value;
        }
    } else {
        n = rnd.next(8, 24);
        k = rnd.next(2, n);
        a.resize(n);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 4) == 0) {
                a[i] = rnd.any(vector<int>{0, 1, 999, 1000});
            } else {
                a[i] = rnd.next(0, 1000);
            }
        }
    }

    println(n, k);
    println(a);

    return 0;
}
