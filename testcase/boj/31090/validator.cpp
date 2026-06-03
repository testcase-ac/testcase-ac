#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int T = inf.readInt(1, 8910, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        int N = inf.readInt(1000, 9999, "N");
        ensuref(N % 100 != 0, "N must not be a multiple of 100: %d", N);
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
