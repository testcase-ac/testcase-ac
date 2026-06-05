#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = 1;
    int k = rnd.next(1, 100000000);
    vector<int> a;

    if (mode == 0) {
        n = rnd.next(1, 5);
        k = rnd.next(1, 20);
        a.assign(n, 0);
        if (rnd.next(2)) {
            int pos = rnd.next(n);
            a[pos] = rnd.next(0, k);
        }
    } else if (mode == 1) {
        n = rnd.next(2, 20);
        k = rnd.next(1, 30);
        a.resize(n);
        for (int i = 0; i < n; ++i) a[i] = rnd.next(0, max(0, k - 1));
    } else if (mode == 2) {
        n = rnd.next(3, 30);
        k = rnd.next(2, 60);
        a.assign(n, 0);
        int i = 0;
        while (i < n) {
            int len = rnd.next(1, min(5, n - i));
            int remaining = k;
            for (int j = 0; j < len; ++j) {
                int slots = len - j;
                int value = (slots == 1) ? remaining : rnd.next(0, remaining);
                a[i + j] = value;
                remaining -= value;
            }
            i += len;
            if (i < n && rnd.next(2)) a[i++] = rnd.next(0, k - 1);
        }
    } else if (mode == 3) {
        n = rnd.next(4, 35);
        k = rnd.next(1, 100);
        a.resize(n);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(100) < 35) {
                a[i] = rnd.next(k, min(100000000, k + rnd.next(0, 200)));
            } else {
                a[i] = rnd.next(0, min(100000000, k + 20));
            }
        }
    } else if (mode == 4) {
        n = rnd.next(10, 60);
        k = rnd.next(20, 200);
        a.resize(n);
        int base = rnd.next(0, k / 2);
        for (int i = 0; i < n; ++i) {
            int wave = (i % 3 == 0) ? rnd.next(k / 2, k + 30) : rnd.next(0, k / 2 + 5);
            a[i] = min(100000000, base + wave);
        }
    } else {
        n = rnd.next(20, 80);
        k = rnd.next(1, 100000000);
        a.resize(n);
        for (int i = 0; i < n; ++i) {
            int choice = rnd.next(100);
            if (choice < 20) {
                a[i] = 0;
            } else if (choice < 45) {
                a[i] = rnd.next(1, min(100000000, k));
            } else {
                a[i] = rnd.next(0, 100000000);
            }
        }
    }

    println(n, k);
    println(a);
    return 0;
}
