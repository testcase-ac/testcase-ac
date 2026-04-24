#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(2, 100000, "N");
    inf.readEoln();

    // Read array of N longs in one line, with strict spacing
    vector<long long> a(N);
    for (int i = 0; i < N; i++) {
        // Name each element for clear errors
        char buf[20];
        sprintf(buf, "a[%d]", i);
        a[i] = inf.readLong(-1000000000LL, 1000000000LL, buf);
        if (i + 1 < N) {
            inf.readSpace();
        }
    }
    inf.readEoln();

    // Check strictly increasing (hence distinct and sorted)
    for (int i = 0; i + 1 < N; i++) {
        ensuref(a[i] < a[i+1],
                "Array not strictly increasing at index %d: %lld >= %lld",
                i, a[i], a[i+1]);
    }

    inf.readEof();
    return 0;
}
