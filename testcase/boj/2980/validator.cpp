#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and L
    int N = inf.readInt(1, 100, "N");
    inf.readSpace();
    int L = inf.readInt(1, 1000, "L");
    inf.readEoln();

    // Read each traffic light
    int prevD = 0;
    for (int i = 0; i < N; i++) {
        int D = inf.readInt(1, L - 1, "D");
        inf.readSpace();
        int R = inf.readInt(1, 100, "R");
        inf.readSpace();
        int G = inf.readInt(1, 100, "G");
        inf.readEoln();

        // Positions must be strictly increasing
        ensuref(D > prevD,
                "Signal %d: position D = %d is not strictly greater than previous position %d",
                i + 1, D, prevD);
        prevD = D;
    }

    inf.readEof();
    return 0;
}
