#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    long long m = inf.readLong(1LL, 2000000000LL, "M");
    inf.readSpace();
    int n = inf.readInt(1, 100000, "N");
    inf.readEoln();

    long long total_requested = 0;
    for (int i = 0; i < n; ++i) {
        long long request = inf.readLong(1LL, 1999999999LL, "request_i");
        inf.readEoln();
        total_requested += request;
    }

    ensuref(total_requested > m, "sum of requests must exceed M: sum=%lld, M=%lld",
            total_requested, m);

    inf.readEof();
}
