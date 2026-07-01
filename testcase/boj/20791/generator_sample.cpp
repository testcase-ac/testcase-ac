#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

const long long MAX_VALUE = 1000000000LL;

vector<long long> makeValues(int n, int mode) {
    vector<long long> values(n);

    if (mode == 0) {
        fill(values.begin(), values.end(), 0);
    } else if (mode == 1) {
        fill(values.begin(), values.end(), MAX_VALUE);
    } else if (mode == 2) {
        long long base = rnd.next(0LL, 20LL);
        for (int i = 0; i < n; ++i) values[i] = (i % 3 == 0 ? 0 : base + i);
    } else if (mode == 3) {
        for (int i = 0; i < n; ++i) values[i] = rnd.next(0LL, 3LL);
    } else {
        long long hi = rnd.next(10LL, MAX_VALUE);
        for (int i = 0; i < n; ++i) values[i] = rnd.next(0LL, hi);
    }

    shuffle(values.begin(), values.end());
    return values;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int tests = rnd.next(4, 8);
    for (int tc = 0; tc < tests; ++tc) {
        int mode = rnd.next(0, 5);
        int n;
        if (tc == 0) {
            n = 1;
        } else if (mode <= 1) {
            n = rnd.next(2, 5);
        } else {
            n = rnd.next(2, 12);
        }

        long long x;
        if (mode == 0) {
            x = 0;
        } else if (mode == 1) {
            x = MAX_VALUE;
        } else if (mode == 2) {
            x = rnd.next(0LL, 5LL);
        } else {
            x = rnd.next(0LL, MAX_VALUE);
        }

        vector<long long> a = makeValues(n, mode);
        vector<long long> b = makeValues(n, rnd.next(0, 5));

        println(n, x);
        println(a);
        println(b);
    }

    return 0;
}
