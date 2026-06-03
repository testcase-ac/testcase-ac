#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    long long n;
    int m;
    vector<long long> called;

    if (mode == 0) {
        n = rnd.next(2LL, 15LL);
        m = rnd.next(0, (int)n - 1);
        for (int i = 0; i < m; ++i) called.push_back(rnd.next(1LL, n));
    } else if (mode == 1) {
        n = rnd.next(3LL, 25LL);
        m = rnd.next(1, min(40, (int)n - 1));
        long long hot = rnd.next(1LL, n);
        for (int i = 0; i < m; ++i) {
            if (rnd.next(0, 3) == 0) {
                called.push_back(rnd.next(1LL, n));
            } else {
                called.push_back(hot);
            }
        }
    } else if (mode == 2) {
        n = rnd.next(2LL, 80LL);
        m = (int)n - 1;
        vector<long long> values;
        for (long long x = 1; x <= n; ++x) values.push_back(x);
        shuffle(values.begin(), values.end());
        called.assign(values.begin(), values.begin() + m);
    } else if (mode == 3) {
        n = rnd.next(999999900LL, 1000000000LL);
        m = rnd.next(0, 24);
        for (int i = 0; i < m; ++i) {
            int bucket = rnd.next(0, 4);
            if (bucket == 0) {
                called.push_back(1);
            } else if (bucket == 1) {
                called.push_back(n);
            } else if (bucket == 2) {
                called.push_back(max(1LL, n - rnd.next(0LL, 30LL)));
            } else {
                called.push_back(rnd.next(1LL, n));
            }
        }
    } else if (mode == 4) {
        n = rnd.next(1000000LL, 1000000000LL);
        m = 0;
    } else if (mode == 5) {
        n = rnd.any(vector<long long>{2LL, 3LL, 1000000LL, 1000001LL, 999999999LL, 1000000000LL});
        m = rnd.next(1, 30);
        for (int i = 0; i < m; ++i) {
            called.push_back(rnd.any(vector<long long>{1LL, 2LL, max(1LL, n - 1), n}));
        }
    } else {
        n = rnd.next(20LL, 200LL);
        m = rnd.next(40, 120);
        for (int i = 0; i < m; ++i) {
            if (rnd.next(0, 1) == 0) {
                called.push_back(rnd.next(1LL, min(n, 10LL)));
            } else {
                called.push_back(rnd.next(max(1LL, n - 10), n));
            }
        }
    }

    m = (int)called.size();
    if (m >= n) {
        called.resize((int)n - 1);
        m = (int)called.size();
    }

    shuffle(called.begin(), called.end());

    println(n, m);
    for (long long x : called) println(x);

    return 0;
}
