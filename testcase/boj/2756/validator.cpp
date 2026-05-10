#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases: at least 1 (as implied by problem) and up to 100000
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    // For each test case, read exactly 12 doubles: 6 darts x,y, each in [-20.0, 20.0]
    for (int tc = 1; tc <= T; tc++) {
        for (int d = 1; d <= 6; d++) {
            // Read x-coordinate
            inf.readDouble(-20.0, 20.0, "x_" + to_string(tc) + "_" + to_string(d));
            inf.readSpace();
            // Read y-coordinate
            inf.readDouble(-20.0, 20.0, "y_" + to_string(tc) + "_" + to_string(d));
            if (d < 6) {
                inf.readSpace();
            } else {
                inf.readEoln();
            }
        }
    }

    inf.readEof();
    return 0;
}
