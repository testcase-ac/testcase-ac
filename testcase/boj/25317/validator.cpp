#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    constexpr int MIN_Q = 1;
    constexpr int MAX_Q = 200000;
    constexpr long long MIN_VALUE = -1000000000000000000LL;
    constexpr long long MAX_VALUE = 1000000000000000000LL;

    int q = inf.readInt(MIN_Q, MAX_Q, "Q");
    inf.readEoln();

    bool hasTypeTwo = false;
    for (int i = 1; i <= q; ++i) {
        int type = inf.readInt(1, 2, "type");
        inf.readSpace();

        if (type == 1) {
            inf.readLong(MIN_VALUE, MAX_VALUE, "a");
            inf.readSpace();
            inf.readLong(MIN_VALUE, MAX_VALUE, "b");
        } else {
            inf.readLong(MIN_VALUE, MAX_VALUE, "c");
            hasTypeTwo = true;
        }

        inf.readEoln();
    }

    ensuref(hasTypeTwo, "at least one type 2 query is required");
    inf.readEof();
}
