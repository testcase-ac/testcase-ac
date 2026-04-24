#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of segments
    int N = inf.readInt(1, 10000, "N");
    inf.readEoln();

    // Each segment: start Xi, end Yi
    for (int i = 0; i < N; i++) {
        int Xi = inf.readInt(1, 10000, "X_i");
        inf.readSpace();
        int Yi = inf.readInt(1, 10000, "Y_i");
        inf.readEoln();
        ensuref(Xi <= Yi,
                "Segment %d has start > end: %d > %d", i+1, Xi, Yi);
    }

    inf.readEof();
    return 0;
}
