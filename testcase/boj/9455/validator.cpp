#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; tc++) {
        setTestCase(tc);

        // Read dimensions m and n
        int m = inf.readInt(1, 100, "m");
        inf.readSpace();
        int n = inf.readInt(1, 100, "n");
        inf.readEoln();

        // Read the grid
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                int v = inf.readInt(0, 1, ("cell_" + to_string(i) + "_" + to_string(j)).c_str());
                if (j < n) {
                    inf.readSpace();
                }
            }
            inf.readEoln();
        }
    }

    inf.readEof();
    return 0;
}
