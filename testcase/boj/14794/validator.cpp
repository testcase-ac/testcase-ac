#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    constexpr long long kMaxN = 1000000000000000000LL;

    int t = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int caseId = 1; caseId <= t; ++caseId) {
        setTestCase(caseId);

        long long n = inf.readLong(1LL, kMaxN, "N");
        inf.readSpace();
        long long k = inf.readLong(1LL, n, "K");
        inf.readEoln();
    }

    inf.readEof();
}
