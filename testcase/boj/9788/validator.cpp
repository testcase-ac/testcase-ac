#include "testlib.h"

#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int tc = inf.readInt(1, 120, "TC");
    inf.readEoln();

    for (int t = 1; t <= tc; ++t) {
        setTestCase(t);

        inf.readEoln();

        int n = inf.readInt(1, 400, "N");
        inf.readSpace();
        inf.readInt(1, n, "K");
        inf.readEoln();

        inf.readInts(n, 1, 999, "L_i");
        inf.readEoln();
    }

    inf.readEof();
}
