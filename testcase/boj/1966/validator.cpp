#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);
        // Read N and M
        int N = inf.readInt(1, 100, "N");
        inf.readSpace();
        int M = inf.readInt(0, N - 1, "M");
        inf.readEoln();

        // Read N priorities
        for (int i = 0; i < N; ++i) {
            if (i > 0) {
                inf.readSpace();
            }
            inf.readInt(1, 9, "priority");
        }
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
