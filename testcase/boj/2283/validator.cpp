#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and K
    int N = inf.readInt(1, 1000, "N");
    inf.readSpace();
    long long K = inf.readLong(1LL, 1000000000LL, "K");
    inf.readEoln();

    struct Segment {
        int L, R;
    };
    vector<Segment> segs;
    segs.reserve(N);

    for (int i = 0; i < N; ++i) {
        int L = inf.readInt(0, 1000000, "L_i");
        inf.readSpace();
        int R = inf.readInt(0, 1000000, "R_i");
        inf.readEoln();

        ensuref(L <= R, "Segment %d has L_i > R_i: %d > %d", i + 1, L, R);
        segs.push_back({L, R});
    }

    // No further global properties are guaranteed by the statement:
    // A,B may or may not exist; no need to check answer existence or uniqueness.
    // Segments may overlap / touch / be nested; all allowed by statement.

    inf.readEof();
}
