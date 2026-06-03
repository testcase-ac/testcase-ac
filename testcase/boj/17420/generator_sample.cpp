#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

const long long LIMIT = 1000000000LL;

long long clampDay(long long x) {
    return max(1LL, min(LIMIT, x));
}

long long nearDeadline(long long b) {
    int pattern = rnd.next(0, 7);
    if (pattern == 0) {
        return b;
    }
    if (pattern == 1) {
        return b + rnd.next(1LL, 30LL);
    }
    if (pattern == 2) {
        return b - rnd.next(1LL, 30LL);
    }
    if (pattern == 3) {
        return b - 30LL * rnd.next(1, 5) + rnd.next(-2LL, 2LL);
    }
    if (pattern == 4) {
        return b + 30LL * rnd.next(1, 4) + rnd.next(-2LL, 2LL);
    }
    if (pattern == 5) {
        return rnd.any(vector<long long>{1LL, 30LL, 31LL, LIMIT - 29LL, LIMIT});
    }
    return rnd.next(1LL, LIMIT);
}

vector<long long> makeUseDays(int n, int mode) {
    vector<long long> b(n);

    if (mode == 0) {
        long long day = rnd.next(1LL, LIMIT);
        fill(b.begin(), b.end(), day);
    } else if (mode == 1) {
        long long start = rnd.next(1LL, LIMIT - n);
        for (int i = 0; i < n; ++i) {
            b[i] = start + i;
        }
    } else if (mode == 2) {
        long long base = rnd.next(1LL, LIMIT - 100);
        for (int i = 0; i < n; ++i) {
            b[i] = base + 30LL * rnd.next(0, 3) + rnd.next(0LL, 3LL);
        }
    } else if (mode == 3) {
        for (int i = 0; i < n; ++i) {
            b[i] = rnd.any(vector<long long>{1LL, 2LL, 29LL, 30LL, 31LL, LIMIT - 1LL, LIMIT});
        }
    } else {
        for (int i = 0; i < n; ++i) {
            b[i] = rnd.next(1LL, LIMIT);
        }
    }

    if (rnd.next(0, 1) == 0) {
        shuffle(b.begin(), b.end());
    }
    return b;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n;
    if (mode == 0) {
        n = rnd.next(1, 3);
    } else if (mode == 4) {
        n = rnd.next(30, 80);
    } else {
        n = rnd.next(4, 18);
    }

    vector<long long> b = makeUseDays(n, mode);
    vector<long long> a(n);
    for (int i = 0; i < n; ++i) {
        a[i] = clampDay(nearDeadline(b[i]));
    }

    if (mode == 3) {
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 3) == 0) {
                a[i] = rnd.any(vector<long long>{1LL, 30LL, 31LL, LIMIT - 30LL, LIMIT});
            }
        }
    }

    println(n);
    println(a);
    println(b);

    return 0;
}
