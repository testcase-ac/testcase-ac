#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const long long MAX_VALUE = 1000000000000000000LL;

    int t = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        long long a = inf.readLong(1LL, MAX_VALUE, "a");
        inf.readSpace();
        long long b = inf.readLong(1LL, MAX_VALUE, "b");
        inf.readEoln();

        long long i = inf.readLong(1LL, MAX_VALUE, "i");
        inf.readSpace();
        int n = inf.readInt(1, 100, "n");
        inf.readEoln();
    }

    inf.readEof();
}
