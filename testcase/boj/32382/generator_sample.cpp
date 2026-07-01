#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n;
    vector<int> a;

    if (mode == 0) {
        n = rnd.next(1, 8);
        a.resize(n);
        for (int& x : a) x = rnd.next(1, 4);
    } else if (mode == 1) {
        n = rnd.next(2, 20);
        int value = rnd.next(1, 20);
        a.assign(n, value);
    } else if (mode == 2) {
        n = rnd.next(3, 30);
        a.resize(n);
        int low = rnd.next(1, 10);
        int high = rnd.next(low, 20);
        for (int& x : a) x = rnd.next(low, high);
    } else if (mode == 3) {
        n = rnd.next(4, 40);
        a.resize(n);
        for (int i = 0; i < n; ++i) a[i] = (i % 2 == 0 ? rnd.next(1, 3) : rnd.next(18, 20));
        shuffle(a.begin(), a.end());
    } else if (mode == 4) {
        n = rnd.next(5, 60);
        a.resize(n);
        int base = rnd.next(1, 16);
        for (int i = 0; i < n; ++i) a[i] = min(20, base + rnd.next(0, 4));
    } else if (mode == 5) {
        n = rnd.next(10, 100);
        a.resize(n);
        for (int& x : a) x = rnd.next(1, 20);
    } else if (mode == 6) {
        n = 100;
        a.resize(n);
        for (int& x : a) x = rnd.next(18, 20);
    } else {
        n = rnd.next(2, 100);
        a.resize(n);
        int total = 0;
        for (int i = 0; i < n; ++i) {
            a[i] = rnd.next(1, 20);
            total += a[i];
        }
        if (total % 2 == 1) {
            int idx = rnd.next(0, n - 1);
            if (a[idx] < 20) {
                ++a[idx];
            } else {
                --a[idx];
            }
        }
    }

    println(n);
    println(a);

    return 0;
}
