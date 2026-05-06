#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of chips
    int n = inf.readInt(1, 10, "n");
    inf.readEoln();

    // Read coordinates of each chip
    for (int i = 0; i < n; i++) {
        inf.readInt(0, 1000, "x_i");
        inf.readSpace();
        inf.readInt(0, 1000, "y_i");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
