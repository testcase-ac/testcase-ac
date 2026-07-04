#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100, "t");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        inf.readLong(1LL, 1000000000LL, "L");
        inf.readSpace();
        inf.readInt(1, 10000, "m");
        inf.readEoln();

        inf.readToken("[a-z]{1,200}", "S_1");
        inf.readEoln();
        inf.readToken("[a-z]{1,200}", "S_2");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
