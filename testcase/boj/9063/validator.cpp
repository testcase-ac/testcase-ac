#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of points
    int N = inf.readInt(1, 100000, "N");
    inf.readEoln();

    // Read each point
    for (int i = 0; i < N; i++) {
        int x = inf.readInt(-10000, 10000, "x_i");
        inf.readSpace();
        int y = inf.readInt(-10000, 10000, "y_i");
        inf.readEoln();
        // No further global constraints (duplicates allowed)
    }

    // No extra data
    inf.readEof();
    return 0;
}
