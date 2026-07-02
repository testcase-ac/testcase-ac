#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    constexpr int MAX_T = 100000;
    constexpr long long MAX_VALUE = 1000000000000000LL;

    int t = inf.readInt(1, MAX_T, "T");
    inf.readEoln();

    for (int i = 1; i <= t; ++i) {
        setTestCase(i);

        inf.readLong(1LL, MAX_VALUE, "a_i");
        inf.readSpace();
        inf.readLong(1LL, MAX_VALUE, "b_i");
        inf.readSpace();
        inf.readLong(1LL, MAX_VALUE, "p_i");
        inf.readSpace();
        inf.readLong(1LL, MAX_VALUE, "q_i");
        inf.readEoln();
    }

    inf.readEof();
}
