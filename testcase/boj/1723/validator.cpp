#include "testlib.h"
#include <cmath>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N, K
    int N = inf.readInt(3, 10000, "N");
    inf.readSpace();
    int K = inf.readInt(3, 1000, "K");
    inf.readEoln();

    // Read N angles
    for (int i = 0; i < N; i++) {
        // 0.0 ≤ angle < 360.0
        double ang = inf.readDouble(0.0, 360.0, "angle");
        ensuref(ang < 360.0,
                "angle at index %d is %.10f but must be strictly less than 360",
                i + 1, ang);
        inf.readEoln();
    }

    // No extra data
    inf.readEof();
    return 0;
}
