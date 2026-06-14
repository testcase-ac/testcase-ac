#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n;
    if (mode == 0) {
        n = 2;
    } else if (mode == 1) {
        n = 3;
    } else if (mode == 7) {
        n = rnd.next(40, 120);
    } else {
        n = rnd.next(4, 18);
    }

    vector<long long> a(n);
    long long low = rnd.next(1LL, 100LL);
    long long high = rnd.next(low, min(1000000000LL, low + rnd.next(0LL, 1000000LL)));

    if (mode == 0 || mode == 1) {
        for (long long& x : a) x = rnd.next(1LL, 1000000000LL);
    } else if (mode == 2) {
        long long first = rnd.next(1LL, 1000000000LL);
        long long second = rnd.next(1LL, 1000000000LL);
        for (int i = 0; i < n; ++i) a[i] = (i % 2 == 0 ? first : second);
    } else if (mode == 3) {
        for (int i = 0; i < n; ++i) a[i] = low + i * rnd.next(0LL, 5LL);
        if (rnd.next(0, 1)) reverse(a.begin(), a.end());
    } else if (mode == 4) {
        long long peak = rnd.next(1LL, 1000000000LL);
        for (int i = 0; i < n; ++i) {
            long long noise = rnd.next(0LL, 20LL);
            a[i] = (i % 2 == 0 ? max(1LL, peak - noise) : rnd.next(1LL, 50LL));
        }
    } else if (mode == 5) {
        vector<long long> pool;
        int distinct = rnd.next(1, 5);
        for (int i = 0; i < distinct; ++i) pool.push_back(rnd.next(1LL, 1000LL));
        for (long long& x : a) x = rnd.any(pool);
    } else if (mode == 6) {
        for (int i = 0; i < n; ++i) a[i] = rnd.next(low, high);
        int l = rnd.next(0, n - 2);
        int r = rnd.next(l + 1, n - 1);
        long long value = rnd.next(1LL, 1000000000LL);
        for (int i = l; i <= r; ++i) a[i] = value;
    } else {
        for (long long& x : a) x = rnd.next(1LL, 1000000000LL);
    }

    println(n);
    println(a);
    return 0;
}
