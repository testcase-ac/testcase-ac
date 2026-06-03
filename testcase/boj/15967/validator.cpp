#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000000, "N");
    inf.readSpace();
    int q1 = inf.readInt(0, 10000, "Q1");
    inf.readSpace();
    int q2 = inf.readInt(0, 10000, "Q2");
    inf.readEoln();

    inf.readInts(n, 1, 1500000, "a_i");
    inf.readEoln();

    int seen_type1 = 0;
    int seen_type2 = 0;
    for (int i = 0; i < q1 + q2; ++i) {
        int type = inf.readInt(1, 2, "query_type");
        inf.readSpace();

        if (type == 1) {
            int left = inf.readInt(1, n, "query_left");
            inf.readSpace();
            int right = inf.readInt(1, n, "query_right");
            // CHECK: The statement gives endpoint bounds separately, but describes an interval from n to m.
            ensuref(left <= right, "type 1 query has left > right at query %d: %d > %d", i + 1, left, right);
            ++seen_type1;
        } else {
            int left = inf.readInt(1, n, "update_left");
            inf.readSpace();
            int right = inf.readInt(1, n, "update_right");
            inf.readSpace();
            inf.readInt(-1000, 1000, "update_delta");
            // CHECK: The statement gives endpoint bounds separately, but describes an interval from s to e.
            ensuref(left <= right, "type 2 query has left > right at query %d: %d > %d", i + 1, left, right);
            ++seen_type2;
        }

        inf.readEoln();
    }

    ensuref(seen_type1 == q2, "expected Q2=%d type 1 queries, found %d", q2, seen_type1);
    ensuref(seen_type2 == q1, "expected Q1=%d type 2 queries, found %d", q1, seen_type2);

    inf.readEof();
}
