#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases T (not specified in statement, so assume 1..100000)
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; tc++) {
        setTestCase(tc);

        // Read K: number of chapters/files
        int K = inf.readInt(3, 5000, "K");
        inf.readEoln();

        // Read the K file sizes
        inf.readLongs(K, 1LL, 10000LL, "size");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
