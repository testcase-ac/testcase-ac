#include "testlib.h"
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // T: number of test cases
    int T = inf.readInt(1, 10, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; ++tc) {
        // N: number of dictionary words
        int N = inf.readInt(1, 50000, "N");
        inf.readEoln();

        for (int i = 0; i < N; ++i) {
            string DW = inf.readToken("[a-z]{1,40}", "DW");
            inf.readEoln();
        }

        // Q: number of queries
        int Q = inf.readInt(1, 50000, "Q");
        inf.readEoln();

        for (int i = 0; i < Q; ++i) {
            string QW = inf.readToken("[a-z]{1,40}", "QW");
            inf.readEoln();
        }
    }

    inf.readEof();
}
