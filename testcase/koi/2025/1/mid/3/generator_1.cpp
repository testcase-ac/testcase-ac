#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

long long randomPower(const vector<long long>& d) {
    int mode = rnd.next(0, 7);
    if (mode == 0) {
        return 1;
    }
    if (mode == 1) {
        return 1000000000LL;
    }
    if (mode == 2) {
        return rnd.any(d);
    }
    if (mode == 3) {
        long long x = rnd.any(d);
        return max(1LL, min(1000000000LL, x + rnd.next(-3, 3)));
    }
    if (mode == 4) {
        long long sum = 0;
        int take = rnd.next(1, min(8, (int)d.size()));
        for (int i = 0; i < take; ++i) {
            sum = min(1000000000LL, sum + rnd.any(d));
        }
        return max(1LL, sum);
    }
    if (mode == 5) {
        return rnd.next(1, 30);
    }
    if (mode == 6) {
        return rnd.next(1, 1000000);
    }
    return rnd.next(1, 1000000000);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int sizeMode = rnd.next(0, 5);
    int n, q;
    if (sizeMode == 0) {
        n = 1;
        q = rnd.next(1, 4);
    } else if (sizeMode == 1) {
        n = rnd.next(2, 5);
        q = rnd.next(1, 8);
    } else if (sizeMode == 2) {
        n = rnd.next(6, 15);
        q = rnd.next(8, 25);
    } else if (sizeMode == 3) {
        n = rnd.next(16, 40);
        q = rnd.next(20, 60);
    } else if (sizeMode == 4) {
        n = rnd.next(41, 120);
        q = rnd.next(60, 160);
    } else {
        n = rnd.next(2, 80);
        q = n;
    }

    vector<long long> d(n);
    int mode = rnd.next(0, 8);
    if (mode == 0) {
        fill(d.begin(), d.end(), rnd.next(1, 20));
    } else if (mode == 1) {
        for (int i = 0; i < n; ++i) {
            d[i] = i + 1;
        }
    } else if (mode == 2) {
        for (int i = 0; i < n; ++i) {
            d[i] = n - i;
        }
    } else if (mode == 3) {
        for (int i = 0; i < n; ++i) {
            d[i] = rnd.next(1, 5);
        }
    } else if (mode == 4) {
        for (int i = 0; i < n; ++i) {
            d[i] = (i % 2 == 0 ? 1 : 1000000000LL);
        }
    } else if (mode == 5) {
        long long base = rnd.next(1, 1000);
        for (int i = 0; i < n; ++i) {
            d[i] = min(1000000000LL, base + rnd.next(0, 3));
        }
    } else if (mode == 6) {
        for (int i = 0; i < n; ++i) {
            d[i] = rnd.next(1, 1000000000);
        }
    } else if (mode == 7) {
        for (int i = 0; i < n; ++i) {
            d[i] = 1LL << rnd.next(0, 29);
        }
    } else {
        for (int i = 0; i < n; ++i) {
            d[i] = rnd.next(1, 100);
        }
        shuffle(d.begin(), d.end());
    }

    println(n, q);
    println(d);

    int queryMode = rnd.next(0, 5);
    for (int j = 1; j <= q; ++j) {
        int x;
        if (queryMode == 0) {
            x = 1;
        } else if (queryMode == 1) {
            x = n;
        } else if (queryMode == 2) {
            x = (j - 1) % n + 1;
        } else if (queryMode == 3) {
            x = n - ((j - 1) % n);
        } else {
            x = rnd.next(1, n);
        }

        long long p;
        if (queryMode == 5) {
            p = randomPower(d);
        } else if (j % 7 == 0) {
            p = 1000000000LL;
        } else if (j % 5 == 0) {
            p = 1;
        } else {
            p = randomPower(d);
        }
        println(x, p);
    }

    return 0;
}
