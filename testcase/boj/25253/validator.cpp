#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(3, 200, "n");
    inf.readSpace();
    int m = inf.readInt(2, 10, "m");
    inf.readEoln();

    int transitionCount = m * m * m;
    for (int i = 0; i < transitionCount; ++i) {
        inf.readInt(1, m, "f_xyz");
        inf.readEoln();
    }

    inf.readInts(n, 1, m, "s0_i");
    inf.readEoln();

    inf.readEof();
    return 0;
}
