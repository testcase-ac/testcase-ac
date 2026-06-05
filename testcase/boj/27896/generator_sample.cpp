#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = 1;
    long long m = 1;
    vector<long long> x;

    if (mode == 0) {
        n = rnd.next(1, 12);
        m = rnd.next(1LL, 20LL);
        x.assign(n, 0);
    } else if (mode == 1) {
        n = rnd.next(1, 15);
        m = rnd.next(1LL, 25LL);
        x.resize(n);
        for (long long& v : x) v = rnd.next(0LL, m);
    } else if (mode == 2) {
        n = rnd.next(2, 18);
        m = rnd.next(2LL, 80LL);
        x.resize(n);
        for (long long& v : x) v = rnd.next(0LL, max(1LL, m / 2));
        x[rnd.next(n)] = rnd.next(m, min(1000000000LL, m + 30));
    } else if (mode == 3) {
        n = rnd.next(3, 25);
        m = rnd.next(1LL, 1000000000LL);
        x.resize(n);
        for (long long& v : x) {
            int bucket = rnd.next(0, 3);
            if (bucket == 0) v = 0;
            else if (bucket == 1) v = rnd.next(1LL, 100LL);
            else if (bucket == 2) v = rnd.next(max(0LL, m - 100), min(1000000000LL, m + 100));
            else v = rnd.next(0LL, 1000000000LL);
        }
    } else if (mode == 4) {
        n = rnd.next(10, 35);
        m = rnd.next(5LL, 200LL);
        x.resize(n);
        long long lo = rnd.next(0LL, 20LL);
        long long hi = rnd.next(lo, min(1000000000LL, lo + rnd.next(0LL, 80LL)));
        for (long long& v : x) v = rnd.next(lo, hi);
    } else {
        n = rnd.next(2, 20);
        m = rnd.next(1LL, 1000000000LL);
        x.resize(n);
        for (long long& v : x) v = rnd.next(900000000LL, 1000000000LL);
        if (rnd.next(0, 1)) {
            for (int i = 0; i < n / 3; ++i) x[rnd.next(n)] = 0;
        }
    }

    if (rnd.next(0, 1)) shuffle(x.begin(), x.end());

    println(n, m);
    println(x);
    return 0;
}
