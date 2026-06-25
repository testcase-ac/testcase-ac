#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int t = rnd.next(1, 2);
    int n = 1;
    long long k = rnd.next(1LL, 30LL);
    vector<long long> x;
    vector<int> y;

    if (mode == 0) {
        n = 1;
        k = rnd.next(1LL, 1000000000LL);
        x = {rnd.next(0LL, 1000000000LL)};
    } else if (mode == 1) {
        n = rnd.next(2, 12);
        k = rnd.next(1LL, 8LL);
        long long cur = rnd.next(0LL, 20LL);
        for (int i = 0; i < n; ++i) {
            if (i > 0) cur += rnd.next(1LL, k);
            x.push_back(cur);
        }
    } else if (mode == 2) {
        n = rnd.next(2, 12);
        k = rnd.next(1LL, 8LL);
        long long cur = rnd.next(0LL, 20LL);
        for (int i = 0; i < n; ++i) {
            if (i > 0) cur += k + rnd.next(1LL, 6LL);
            x.push_back(cur);
        }
    } else if (mode == 3) {
        n = rnd.next(3, 14);
        k = rnd.next(2LL, 10LL);
        long long cur = rnd.next(0LL, 10LL);
        for (int i = 0; i < n; ++i) {
            if (i > 0) {
                if (rnd.next(0, 99) < 65) cur += rnd.next(1LL, k);
                else cur += k + rnd.next(1LL, 10LL);
            }
            x.push_back(cur);
        }
    } else if (mode == 4) {
        n = rnd.next(2, 10);
        k = rnd.any(vector<long long>{1LL, 2LL, 1000000000LL});
        long long cur = 1000000000LL - rnd.next(0LL, 100LL);
        x.push_back(cur);
        for (int i = 1; i < n; ++i) {
            long long gap = (k == 1000000000LL ? rnd.next(1LL, 20LL) : rnd.next(1LL, k + 2));
            cur -= gap;
            x.push_back(cur);
        }
        sort(x.begin(), x.end());
    } else {
        n = rnd.next(5, 16);
        k = rnd.next(3LL, 12LL);
        long long cur = rnd.next(0LL, 15LL);
        int remaining = n;
        while (remaining > 0) {
            int groupSize = rnd.next(1, min(remaining, 5));
            for (int i = 0; i < groupSize; ++i) {
                if (!x.empty()) cur += rnd.next(1LL, k);
                x.push_back(cur);
            }
            remaining -= groupSize;
            if (remaining > 0) cur += k + rnd.next(1LL, 12LL);
        }
    }

    for (int i = 0; i < n; ++i) {
        if (mode == 4 && rnd.next(0, 4) == 0) y.push_back(rnd.any(vector<int>{1, 10000}));
        else y.push_back(rnd.next(1, 10000));
    }

    println(t, n, k);
    for (int i = 0; i < n; ++i) {
        println(x[i], y[i]);
    }

    return 0;
}
