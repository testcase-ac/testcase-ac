#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int k = inf.readInt(1, n, "K");
    inf.readSpace();
    inf.readInt(1, 100, "C");
    inf.readSpace();
    inf.readInt(1, 100, "R");
    inf.readEoln();

    inf.readInts(k, 1, 100000, "base_i");
    inf.readEoln();

    inf.readInts(k, 1, 100, "s_i");
    inf.readEoln();

    inf.readInts(k, 1, 100, "p_i");
    inf.readEoln();

    for (int day = 1; day <= n; ++day) {
        inf.readInt(0, k, "l_i");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
