#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(0, 100, "N");
    inf.readEoln();

    for (int tc = 1; tc <= n; ++tc) {
        setTestCase(tc);
        inf.readToken("[0-9]{1,40}", "digits");
        inf.readEoln();
    }

    inf.readEof();
}
