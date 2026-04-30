#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of points
    int n = inf.readInt(2, 100000, "n");
    inf.readEoln();

    // Read each point's coordinates
    for (int i = 0; i < n; i++) {
        int x = inf.readInt(-10000, 10000, "x_i");
        inf.readSpace();
        int y = inf.readInt(-10000, 10000, "y_i");
        inf.readEoln();
        // No uniqueness constraint: duplicate points are allowed
    }

    inf.readEof();
    return 0;
}
