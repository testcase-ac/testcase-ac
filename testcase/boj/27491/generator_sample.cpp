#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 20);
    vector<long long> a(n);

    if (mode == 0) {
        for (long long& x : a) x = -rnd.next(1, 25);
    } else if (mode == 1) {
        for (long long& x : a) x = rnd.next(0, 25);
    } else if (mode == 2) {
        for (long long& x : a) x = rnd.next(-3, 3);
        if (rnd.next(0, 1)) {
            int pos = rnd.next(0, n - 1);
            a[pos] = 0;
        }
    } else if (mode == 3) {
        for (int i = 0; i < n; ++i) {
            long long value = rnd.next(1, 15);
            a[i] = (i % 2 == 0 ? value : -value - rnd.next(-2, 2));
        }
        if (rnd.next(0, 1)) reverse(a.begin(), a.end());
    } else if (mode == 4) {
        long long balance = 0;
        for (int i = 0; i < n; ++i) {
            if (i + 1 == n && rnd.next(0, 2) == 0) {
                a[i] = -balance;
            } else {
                a[i] = rnd.next(-12, 12);
                balance += a[i];
            }
        }
    } else {
        long long limit = rnd.next(10, 1000000000);
        for (long long& x : a) x = rnd.next(-limit, limit);
    }

    println(n);
    println(a);
    return 0;
}
