#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int T = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        int R = inf.readInt(1, 25, "R");
        inf.readSpace();
        int C = inf.readInt(1, 25, "C");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
