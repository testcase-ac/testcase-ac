#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const long long MAX_L = 1000000000000000000LL;

    int q = inf.readInt(1, 150000, "Q");
    inf.readEoln();

    long long m = 1;
    long long adHocLengthSum = 0;
    bool hasQuery = false;

    for (int i = 1; i <= q; ++i) {
        std::string op = inf.readToken("query|ad-hoc", "op");
        inf.readSpace();

        if (op == "query") {
            long long x = inf.readLong(0LL, m - 1, "x");
            inf.readSpace();
            long long l = inf.readLong(1LL, MAX_L, "L");
            inf.readEoln();

            (void)x;
            (void)l;
            hasQuery = true;
        } else {
            long long k = inf.readLong(0LL, m - 1, "k");
            inf.readSpace();
            long long l = inf.readLong(1LL, MAX_L, "L");
            inf.readEoln();

            ensuref(adHocLengthSum <= MAX_L - l,
                    "sum of ad-hoc lengths exceeds 10^18 at operation %d", i);
            adHocLengthSum += l;
            ++m;

            (void)k;
        }
    }

    ensuref(hasQuery, "at least one query is required");
    inf.readEof();
}
