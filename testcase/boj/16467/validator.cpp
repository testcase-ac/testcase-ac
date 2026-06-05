#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int T = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        inf.readInt(0, 10, "K");
        inf.readSpace();
        inf.readInt(1, 100000000, "N");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
