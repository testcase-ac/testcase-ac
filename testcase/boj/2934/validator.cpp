#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of days/plants
    int N = inf.readInt(1, 100000, "N");
    inf.readEoln();

    // For each day, read L and R
    for (int i = 1; i <= N; i++) {
        int L = inf.readInt(1, 100000, "L");
        inf.readSpace();
        int R = inf.readInt(1, 100000, "R");
        inf.readEoln();

        // Ensure L < R
        ensuref(L < R,
                "Line %d: L (%d) must be less than R (%d)",
                i + 1, L, R);
    }

    inf.readEof();
    return 0;
}
