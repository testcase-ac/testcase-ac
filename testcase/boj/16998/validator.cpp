#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read W
    int W = inf.readInt(1, 100000, "W");
    inf.readEoln();

    for (int t = 0; t < W; ++t) {
        int p = inf.readInt(1, 1000000, "p");
        inf.readSpace();
        int q = inf.readInt(1, 1000000, "q");
        inf.readSpace();
        int n = inf.readInt(1, 1000000, "n");
        inf.readEoln();
    }

    inf.readEof();
}
