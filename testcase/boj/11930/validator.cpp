#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of points
    int N = inf.readInt(1, 1000, "N");
    inf.readEoln();

    // Read each point's coordinates
    for (int i = 0; i < N; i++) {
        inf.readInt(-1000000, 1000000, "x_i");
        inf.readSpace();
        inf.readInt(-1000000, 1000000, "y_i");
        inf.readSpace();
        inf.readInt(-1000000, 1000000, "z_i");
        inf.readEoln();
    }

    // No extra data
    inf.readEof();
    return 0;
}
