#include "testlib.h"

#include <vector>
using namespace std;

int makeValue(int parity, int profile) {
    if (profile == 0) {
        return parity ? rnd.next(1, 19) | 1 : (rnd.next(1, 10) * 2);
    }
    if (profile == 1) {
        int base = rnd.next(1, 1000000000);
        return parity ? (base * 2 - 1) : (base * 2);
    }

    int limit = 2147483647;
    if (parity) {
        return limit - 2 * rnd.next(0, 20);
    }
    return limit - 1 - 2 * rnd.next(0, 20);
}

void forceOddCount(vector<int>& a) {
    int odd_count = 0;
    for (int x : a) {
        odd_count += x % 2;
    }
    if (odd_count % 2 == 0) {
        int pos = rnd.next((int)a.size());
        if (a[pos] % 2 == 0) {
            --a[pos];
        } else if (a[pos] == 2147483647) {
            --a[pos];
        } else {
            ++a[pos];
        }
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int profile = rnd.next(0, 2);
    int n;
    if (mode == 0) {
        n = rnd.next(1, 4);
    } else if (mode == 5) {
        n = rnd.next(80, 180);
    } else {
        n = rnd.next(5, 35);
    }

    vector<int> a(n);
    if (mode == 0) {
        for (int i = 0; i < n; ++i) {
            a[i] = makeValue(rnd.next(0, 1), profile);
        }
    } else if (mode == 1) {
        for (int i = 0; i < n; ++i) {
            a[i] = makeValue(i % 2, profile);
        }
    } else if (mode == 2) {
        for (int i = 0; i < n; ++i) {
            a[i] = makeValue((i / rnd.next(1, 4)) % 2, profile);
        }
    } else if (mode == 3) {
        int odd_pos = rnd.next(n);
        for (int i = 0; i < n; ++i) {
            a[i] = makeValue(i == odd_pos, profile);
        }
    } else if (mode == 4) {
        for (int i = 0; i < n; ++i) {
            bool near_end = i < 3 || i + 3 >= n;
            a[i] = makeValue(near_end ? rnd.next(0, 1) : rnd.next(0, 3) == 0, profile);
        }
    } else {
        for (int i = 0; i < n; ++i) {
            a[i] = makeValue(rnd.next(0, 5) == 0, profile);
        }
    }

    forceOddCount(a);

    println(n);
    println(a);
    return 0;
}
