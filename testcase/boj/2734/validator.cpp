#include "testlib.h"

#include <cmath>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 1000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, 10, "N");
        vector<double> x(n);

        for (int i = 0; i < n; ++i) {
            inf.readSpace();
            // CHECK: The statement gives no x-coordinate bound; keep a broad practical cap.
            x[i] = inf.readDouble(-1e9, 1e9, "x_i");
            if (i > 0) {
                double distance = x[i] - x[i - 1];
                ensuref(distance >= 2.0 - 1e-9 && distance <= 3.4 + 1e-9,
                        "adjacent distance at index %d is %.17g, expected [2.0, 3.4]",
                        i, distance);
            }
        }

        inf.readEoln();
    }

    inf.readEof();
}
