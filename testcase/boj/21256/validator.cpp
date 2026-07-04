#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The statement does not give an explicit upper bound for T, so use
    // the local multi-case default while enforcing the stated total string size.
    int t = inf.readInt(1, 100000, "T");
    inf.readEoln();

    long long totalLength = 0;
    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        inf.readLong(-1000000000LL, 1000000000LL, "m_x");
        inf.readSpace();
        inf.readLong(-1000000000LL, 1000000000LL, "m_y");
        inf.readEoln();

        std::string s = inf.readToken("[UDLR]{1,100000}", "s");
        inf.readEoln();

        totalLength += static_cast<long long>(s.size());
        ensuref(totalLength <= 1000000LL,
                "sum of string lengths exceeds 1000000 at test case %d", tc);
    }

    inf.readEof();
    return 0;
}
