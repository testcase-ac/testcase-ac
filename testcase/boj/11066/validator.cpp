#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        // Number of chapters K
        int K = inf.readInt(3, 500, "K");
        inf.readEoln();

        // File sizes for each chapter
        inf.readInts(K, 1, 10000, "size_i");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
