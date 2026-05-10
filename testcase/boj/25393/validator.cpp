#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of intervals
    int N = inf.readInt(1, 300000, "N");
    inf.readEoln();

    // Read intervals
    for (int i = 0; i < N; i++) {
        int l = inf.readInt(0, 1000000, "l_i");
        inf.readSpace();
        int r = inf.readInt(0, 1000000, "r_i");
        ensuref(l < r,
                "Interval at index %d is invalid: l_i (%d) must be < r_i (%d)", 
                i, l, r);
        inf.readEoln();
    }

    // Number of queries
    int Q = inf.readInt(1, 300000, "Q");
    inf.readEoln();

    // Read queries
    for (int i = 0; i < Q; i++) {
        int lq = inf.readInt(0, 1000000, "l_q");
        inf.readSpace();
        int rq = inf.readInt(0, 1000000, "r_q");
        ensuref(lq < rq,
                "Query at index %d is invalid: l_q (%d) must be < r_q (%d)", 
                i, lq, rq);
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
