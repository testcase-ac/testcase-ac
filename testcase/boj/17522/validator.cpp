#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of houses
    int n = inf.readInt(1, 300000, "n");
    inf.readEoln();

    // Read each house coordinate
    for (int i = 0; i < n; i++) {
        int x = inf.readInt(-1000000000, 1000000000, "x_i");
        inf.readSpace();
        int y = inf.readInt(-1000000000, 1000000000, "y_i");
        inf.readEoln();
        // No other global constraints (duplicates allowed)
    }

    inf.readEof();
    return 0;
}
