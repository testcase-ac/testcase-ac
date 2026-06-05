#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 30);
    long long k = rnd.next(-20, 20);
    vector<long long> a(n);

    if (mode == 0) {
        k = rnd.next(-1000000000LL, 1000000000LL);
        for (int i = 0; i < n; ++i) {
            a[i] = k;
        }
    } else if (mode == 1) {
        int step = rnd.next(1, 20);
        for (int i = 0; i < n; ++i) {
            long long delta = (i % 2 == 0 ? step : -step);
            a[i] = k + delta;
        }
    } else if (mode == 2) {
        for (int i = 0; i < n; ++i) {
            long long delta = rnd.next(-10, 10);
            a[i] = k + delta;
        }
    } else if (mode == 3) {
        for (int i = 0; i < n; ++i) {
            long long delta = rnd.next(1, 25);
            a[i] = k + delta;
        }
    } else if (mode == 4) {
        k = rnd.next(0, 1) == 0 ? -1000000000LL : 1000000000LL;
        for (int i = 0; i < n; ++i) {
            a[i] = k;
        }
        if (n > 1) {
            int pos = rnd.next(0, n - 1);
            a[pos] = (k == -1000000000LL ? -999999999LL : 999999999LL);
        }
    } else {
        n = rnd.next(2, 30);
        a.assign(n, 0);
        int pairs = n / 2;
        for (int i = 0; i < pairs; ++i) {
            long long delta = rnd.next(1, 30);
            a[2 * i] = k + delta;
            a[2 * i + 1] = k - delta;
        }
        if (n % 2 == 1) {
            a.back() = k + rnd.next(-5, 5);
        }
        shuffle(a.begin(), a.end());
    }

    println(n, k);
    for (int i = 0; i < n; ++i) {
        if (i > 0) {
            cout << ' ';
        }
        cout << a[i];
    }
    cout << '\n';
    return 0;
}
