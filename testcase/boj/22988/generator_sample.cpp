#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

long long clampValue(long long value, long long x) {
    if (value < 0) return 0;
    if (value > x) return x;
    return value;
}

long long randomNear(long long center, long long radius, long long x) {
    long long lo = max(0LL, center - radius);
    long long hi = min(x, center + radius);
    return rnd.next(lo, hi);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 30);

    long long x;
    if (mode == 0) {
        x = rnd.next(1LL, 20LL);
    } else if (mode == 1) {
        x = rnd.next(1LL, 1000LL);
    } else if (mode == 2) {
        x = rnd.next(999999999999999900LL, 1000000000000000000LL);
    } else {
        x = rnd.next(1LL, 1000000000000000000LL);
    }

    long long need = (x + 1) / 2;
    vector<long long> c;

    if (mode == 0) {
        for (int i = 0; i < n; ++i) {
            c.push_back(rnd.next(0LL, x));
        }
    } else if (mode == 1) {
        while ((int)c.size() < n) {
            int choice = rnd.next(0, 3);
            if (choice == 0) c.push_back(0);
            if (choice == 1) c.push_back(x);
            if (choice == 2) c.push_back(randomNear(need, min(10LL, x), x));
            if (choice == 3) c.push_back(rnd.next(0LL, max(0LL, need - 1)));
        }
    } else if (mode == 2) {
        while ((int)c.size() + 1 < n) {
            long long a = rnd.next(0LL, x);
            long long slack = rnd.next(-2LL, 2LL);
            long long b = clampValue(need - a + slack, x);
            c.push_back(a);
            c.push_back(b);
        }
        if ((int)c.size() < n) c.push_back(rnd.next(0LL, x));
    } else if (mode == 3) {
        for (int i = 0; i < n; ++i) {
            long long upper = max(0LL, need - 1);
            c.push_back(rnd.next(0LL, upper));
        }
    } else if (mode == 4) {
        for (int i = 0; i < n; ++i) {
            if (i % 4 == 0) {
                c.push_back(x);
            } else if (i % 4 == 1) {
                c.push_back(0);
            } else {
                c.push_back(randomNear(need, min(1000LL, x), x));
            }
        }
    } else {
        n = rnd.next(25, 60);
        for (int i = 0; i < n; ++i) {
            int bucket = rnd.next(0, 5);
            if (bucket == 0) c.push_back(0);
            if (bucket == 1) c.push_back(x);
            if (bucket == 2) c.push_back(rnd.next(0LL, max(0LL, need - 1)));
            if (bucket == 3) c.push_back(randomNear(need, min(1000000LL, x), x));
            if (bucket == 4) c.push_back(rnd.next(need, x));
            if (bucket == 5) c.push_back(rnd.next(0LL, x));
        }
    }

    shuffle(c.begin(), c.end());

    println((int)c.size(), x);
    println(c);

    return 0;
}
