#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 30);
    vector<long long> a(n);

    if (mode == 0) {
        long long h = rnd.next(1, 20);
        fill(a.begin(), a.end(), h);
    } else if (mode == 1) {
        long long start = rnd.next(1, 5);
        long long step = rnd.next(1, 4);
        for (int i = 0; i < n; ++i) {
            a[i] = start + step * i;
        }
    } else if (mode == 2) {
        long long peak = rnd.next(2, 25);
        for (int i = 0; i < n; ++i) {
            long long rise = 1 + (i % peak);
            long long noise = rnd.next(0, 3);
            a[i] = rise + noise;
        }
    } else if (mode == 3) {
        int block = rnd.next(2, 7);
        for (int i = 0; i < n; ++i) {
            if (i % block == 0) {
                a[i] = rnd.next(1, 2);
            } else {
                a[i] = rnd.next(2, 30);
            }
        }
    } else if (mode == 4) {
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 4) == 0) {
                a[i] = rnd.next(100000000LL, 1000000000LL);
            } else {
                a[i] = rnd.next(1, 20);
            }
        }
    } else {
        long long current = rnd.next(1, 12);
        for (int i = 0; i < n; ++i) {
            current += rnd.next(-3, 4);
            current = max(1LL, min(35LL, current));
            a[i] = current;
        }
    }

    println(n);
    println(a);

    return 0;
}
