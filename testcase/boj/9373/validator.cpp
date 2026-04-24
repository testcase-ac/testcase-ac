#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases
    int T = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        // Corridor width w
        int w = inf.readInt(1, 100000, "w");
        inf.readEoln();

        // Number of sensors n
        int n = inf.readInt(0, 1000, "n");
        inf.readEoln();

        for (int i = 0; i < n; ++i) {
            // Sensor center x: 0 <= x <= w
            int x = inf.readInt(0, w, "x_i");
            inf.readSpace();
            // Sensor center y: -100000 <= y <= 100000
            int y = inf.readInt(-100000, 100000, "y_i");
            inf.readSpace();
            // Sensor radius r: 1 <= r <= 100000
            int r = inf.readInt(1, 100000, "r_i");
            inf.readEoln();

            // No further positional constraints: sensors may overlap walls
        }
    }

    inf.readEof();
    return 0;
}
