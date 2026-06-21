#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

long long nearValue(long long center, long long radius) {
    const long long maxN = 1000000000000000000LL;
    long long lo = center > radius ? center - radius : 1LL;
    long long hi = center > maxN - radius ? maxN : center + radius;
    return rnd.next(lo, hi);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long maxN = 1000000000000000000LL;
    int t = rnd.next(6, 30);

    vector<long long> ns;
    ns.push_back(rnd.next(1, 6));
    ns.push_back(rnd.next(7, 100));

    while ((int)ns.size() < t) {
        int mode = rnd.next(0, 7);
        long long n;

        if (mode == 0) {
            n = rnd.next(1, 20);
        } else if (mode == 1) {
            n = rnd.next(21, 1000);
        } else if (mode == 2) {
            n = nearValue(rnd.next(1, 12), rnd.next(0, 3));
        } else if (mode == 3) {
            long long base = 1LL << rnd.next(0, 59);
            n = nearValue(base, rnd.next(0, 5));
        } else if (mode == 4) {
            long long base = 1000000007LL * rnd.next(1LL, 1000000LL);
            n = nearValue(base, rnd.next(0, 1000));
        } else if (mode == 5) {
            n = rnd.next(1000000000000LL, maxN);
        } else {
            n = nearValue(maxN, rnd.next(0LL, 1000000LL));
        }

        ns.push_back(n);
    }

    shuffle(ns.begin(), ns.end());

    println((int)ns.size());
    for (long long n : ns) {
        println(n);
    }

    return 0;
}
