#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000000, "N");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        long long enter = inf.readLong(0LL, 2100000000LL, "T_E");
        inf.readSpace();
        long long exit = inf.readLong(0LL, 2100000000LL, "T_X");
        inf.readEoln();

        ensuref(enter < exit, "interval %d must satisfy T_E < T_X: %lld >= %lld",
                i + 1, enter, exit);
    }

    inf.readEof();
}
