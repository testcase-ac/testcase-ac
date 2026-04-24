#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; tc++) {
        setTestCase(tc);

        // n: size of the sequence
        int n = inf.readInt(1, 100, "n");
        inf.readEoln();

        // R: each r_i is an integer 0 <= r_i <= n-1
        for (int i = 1; i <= n; i++) {
            string name = "r_" + to_string(i);
            int ri = inf.readInt(0, n - 1, name);
            if (i < n) {
                inf.readSpace();
            } else {
                inf.readEoln();
            }
        }
    }

    inf.readEof();
    return 0;
}
