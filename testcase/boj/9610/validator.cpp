#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of points
    int n = inf.readInt(1, 1000, "n");
    inf.readEoln();

    // Each point's coordinates
    for (int i = 0; i < n; i++) {
        inf.readInt(-1000000, 1000000, "x_i");
        inf.readSpace();
        inf.readInt(-1000000, 1000000, "y_i");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
