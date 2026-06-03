#include "testlib.h"
#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int sizeMode = rnd.next(100);
    int n;
    if (sizeMode < 15) {
        n = 1;
    } else if (sizeMode < 65) {
        n = rnd.next(2, 12);
    } else if (sizeMode < 90) {
        n = rnd.next(13, 40);
    } else {
        n = rnd.next(41, 120);
    }

    vector<int> a(n);
    int mode = rnd.next(8);

    if (mode == 0) {
        fill(a.begin(), a.end(), 0);
    } else if (mode == 1) {
        int value = rnd.next(0, 1000000);
        fill(a.begin(), a.end(), value);
    } else if (mode == 2) {
        int hi = rnd.next(0, 20);
        for (int& x : a) x = rnd.next(0, hi);
    } else if (mode == 3) {
        int hi = rnd.next(1000, 1000000);
        for (int& x : a) x = rnd.next(0, hi);
    } else if (mode == 4) {
        int large = rnd.next(900000, 1000000);
        for (int& x : a) x = rnd.next(0, 3);
        a[rnd.next(n)] = large;
    } else if (mode == 5) {
        int nonZero = rnd.next(1, max(1, n / 3));
        fill(a.begin(), a.end(), 0);
        for (int i = 0; i < nonZero; ++i) a[i] = rnd.next(1, 1000000);
        shuffle(a.begin(), a.end());
    } else if (mode == 6) {
        int start = rnd.next(0, 100);
        int step = rnd.next(0, 10000);
        for (int i = 0; i < n; ++i) {
            long long value = start + 1LL * i * step;
            a[i] = static_cast<int>(min(1000000LL, value));
        }
        if (rnd.next(2)) reverse(a.begin(), a.end());
    } else {
        vector<int> pool = {0, 1, 2, 3, 5, 8, 13, 21, 1000, 999999, 1000000};
        for (int& x : a) x = rnd.any(pool);
    }

    println(n);
    println(a);

    return 0;
}
