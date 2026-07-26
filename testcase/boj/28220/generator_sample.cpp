#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(1, 12);
    int width = rnd.any(vector<int>{0, 1, rnd.next(2, 10), 100});
    long long l = rnd.any(vector<long long>{
        0LL, rnd.next(0LL, 50LL), 1000000000LL - width});
    long long r = l + width;
    vector<long long> a(n);

    int mode = rnd.next(0, 4);
    if (mode == 0) {
        for (long long& x : a)
            x = rnd.next(max(0LL, l - 5), min(1000000000LL, r + 5));
    } else if (mode == 1) {
        for (int i = 0; i < n; ++i)
            a[i] = i % 2 == 0 ? 0 : 1000000000LL;
    } else if (mode == 2) {
        vector<long long> values{0LL, l, r, 1000000000LL};
        for (long long& x : a)
            x = rnd.any(values);
    } else if (mode == 3) {
        for (long long& x : a)
            x = rnd.next(l, r);
        sort(a.begin(), a.end());
        shuffle(a.begin(), a.end());
    } else {
        long long x = rnd.any(vector<long long>{0LL, l, r, 1000000000LL});
        fill(a.begin(), a.end(), x);
    }

    println(n, l, r);
    println(a);
}
