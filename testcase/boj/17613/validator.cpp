#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read T
    int T = inf.readInt(1, 2000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; ++tc) {
        // Read x and y
        int x = inf.readInt(1, 1000000000, "x");
        inf.readSpace();
        int y = inf.readInt(x, 1000000000, "y");
        inf.readEoln();
    }

    inf.readEof();
}
