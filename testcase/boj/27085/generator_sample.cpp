#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int smallValue(int magnitude) {
    int value = rnd.next(1, magnitude);
    return rnd.next(2) == 0 ? -value : value;
}

long long largeValue() {
    long long value = rnd.next(100000000, 1000000000);
    return rnd.next(2) == 0 ? -value : value;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(6);
    int n = rnd.next(1, 25);
    int s = rnd.next(1, n);
    vector<long long> a(n);

    if (mode == 0) {
        for (int i = 0; i < n; ++i) {
            a[i] = rnd.next(0, 5) == 0 ? 0 : smallValue(8);
        }
    } else if (mode == 1) {
        for (int i = 0; i < n; ++i) {
            int dist = abs(i - (s - 1));
            int sign = dist % 2 == 0 ? 1 : -1;
            a[i] = sign * rnd.next(1, 12);
        }
    } else if (mode == 2) {
        for (int i = 0; i < n; ++i) {
            int dist = abs(i - (s - 1));
            if (dist <= 1) {
                a[i] = rnd.next(1, 9);
            } else if (dist == 2) {
                a[i] = -rnd.next(5, 18);
            } else {
                a[i] = smallValue(20);
            }
        }
    } else if (mode == 3) {
        s = rnd.any(vector<int>{1, n});
        for (int i = 0; i < n; ++i) {
            a[i] = rnd.next(0, 3) == 0 ? 0 : smallValue(30);
        }
    } else if (mode == 4) {
        for (int i = 0; i < n; ++i) {
            a[i] = rnd.next(0, 4) == 0 ? largeValue() : smallValue(50);
        }
    } else {
        n = rnd.next(8, 30);
        s = rnd.next(2, n - 1);
        a.assign(n, 0);
        for (int i = s - 2; i >= 0; --i) {
            a[i] = (s - 1 - i) % 2 == 1 ? rnd.next(3, 15) : -rnd.next(1, 12);
        }
        for (int i = s; i < n; ++i) {
            a[i] = (i - s) % 2 == 0 ? -rnd.next(1, 12) : rnd.next(3, 15);
        }
    }

    a[s - 1] = 0;

    println(n, s);
    println(a);

    return 0;
}
