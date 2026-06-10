#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 20, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        inf.readLong(1LL, 1000000000LL, "A");
        inf.readSpace();
        inf.readLong(1LL, 1000000000LL, "B");
        inf.readSpace();
        inf.readLong(1LL, 2000000000LL, "X");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
