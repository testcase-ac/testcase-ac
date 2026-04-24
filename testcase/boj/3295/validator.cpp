#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases T
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; tc++) {
        setTestCase(tc);

        // Read n (number of nodes) and m (number of directed edges)
        int n = inf.readInt(1, 1000, "n");
        inf.readSpace();
        int m = inf.readInt(0, 50000, "m");
        inf.readEoln();

        // Read each directed edge u -> v
        for (int i = 0; i < m; i++) {
            inf.readInt(0, n-1, "u_i");
            inf.readSpace();
            inf.readInt(0, n-1, "v_i");
            inf.readEoln();
        }
    }

    inf.readEof();
    return 0;
}
