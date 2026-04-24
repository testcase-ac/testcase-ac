#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // First line: W0, I0, T
    int W0 = inf.readInt(1, 10000000, "W0");
    inf.readSpace();
    int I0 = inf.readInt(1, 100000, "I0");
    inf.readSpace();
    int T  = inf.readInt(1, 1000, "T");
    inf.readEoln();

    // Second line: D, I, A
    int D = inf.readInt(1, 1000, "D");
    inf.readSpace();
    int I = inf.readInt(0, 100000, "I");
    inf.readSpace();
    int A = inf.readInt(0, 100000, "A");
    inf.readEoln();

    // Global implied constraint:
    // During the diet, weight should never increase.
    // Per day weight change (without basal adjustments) = I - (I0 + A).
    // To avoid any increase, we require I <= I0 + A.
    ensuref((long long)I <= (long long)I0 + A,
            "During diet weight increases: I (%d) > I0 + A (%d)", I, I0 + A);

    inf.readEof();
    return 0;
}
