#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 20, "N");
    inf.readSpace();
    int b = inf.readInt(1, 20, "B");
    inf.readEoln();

    for (int i = 1; i <= b; ++i) {
        inf.readInt(1, n, "K_i");
        inf.readSpace();
        inf.readInt(1, 40000, "P_i");
        inf.readSpace();
        inf.readInt(1, 1000, "A_i");
        inf.readEoln();
    }

    for (int cow = 1; cow <= n; ++cow) {
        inf.readInts(n, 1, 1000, "s_ij");
        inf.readEoln();
    }

    inf.readEof();
}
