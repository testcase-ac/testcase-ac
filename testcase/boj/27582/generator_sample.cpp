#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n = rnd.next(1, 30);
    vector<long long> a;
    a.reserve(n);

    if (mode == 0) {
        n = rnd.next(1, 5);
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.any(vector<long long>{0, 1, 1000000000LL}));
        }
    } else if (mode == 1) {
        long long start = rnd.next(0, 20);
        long long step = rnd.next(0, 3);
        for (int i = 0; i < n; ++i) {
            a.push_back(min(1000000000LL, start + step * i));
        }
    } else if (mode == 2) {
        long long start = rnd.next(0, 20);
        long long step = rnd.next(0, 3);
        for (int i = 0; i < n; ++i) {
            a.push_back(max(0LL, start - step * i));
        }
    } else if (mode == 3) {
        int distinct = rnd.next(1, 6);
        vector<long long> values;
        for (int i = 0; i < distinct; ++i) {
            values.push_back(rnd.next(0, 25));
        }
        sort(values.begin(), values.end());
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.any(values));
        }
    } else if (mode == 4) {
        long long low = rnd.next(0, 10);
        long long high = rnd.next(999999990LL, 1000000000LL);
        for (int i = 0; i < n; ++i) {
            long long jitter = rnd.next(0, 3);
            a.push_back((i % 2 == 0) ? high - jitter : low + jitter);
        }
    } else if (mode == 5) {
        int blocks = rnd.next(2, 6);
        for (int b = 0; b < blocks; ++b) {
            int len = rnd.next(1, 5);
            long long base = rnd.next(0, 20);
            for (int i = 0; i < len; ++i) {
                a.push_back(base + rnd.next(0, 4));
            }
        }
        n = (int)a.size();
    } else {
        long long lo = rnd.next(0, 100);
        long long hi = rnd.next(lo, min(1000000000LL, lo + rnd.next(0, 100)));
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.next(lo, hi));
        }
    }

    println(n);
    println(a);
    return 0;
}
