#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const long long MAX_COUNT = 100000000000000000LL;

    int t = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        inf.readLong(0LL, MAX_COUNT, "a");
        inf.readSpace();
        inf.readLong(0LL, MAX_COUNT, "b");
        inf.readSpace();
        inf.readLong(0LL, MAX_COUNT, "c");
        inf.readSpace();
        inf.readLong(0LL, MAX_COUNT, "d");
        inf.readEoln();
    }

    inf.readEof();
}
