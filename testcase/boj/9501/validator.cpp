#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases
    int T = inf.readInt(1, 50, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        // For each test case, read N and D
        int N = inf.readInt(1, 100, "N");
        inf.readSpace();
        int D = inf.readInt(1, 1000000, "D");
        inf.readEoln();

        // Read N lines of (v_i, f_i, c_i)
        for (int i = 0; i < N; ++i) {
            // Use indexed names to improve error messages
            string vs = "v_" + to_string(i + 1);
            string fs = "f_" + to_string(i + 1);
            string cs = "c_" + to_string(i + 1);

            inf.readInt(1, 1000, vs.c_str());
            inf.readSpace();
            inf.readInt(1, 1000, fs.c_str());
            inf.readSpace();
            inf.readInt(1, 1000, cs.c_str());
            inf.readEoln();
        }
    }

    inf.readEof();
    return 0;
}
