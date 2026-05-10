#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 3000, "N");
    inf.readEoln();

    // Read each segment
    for (int i = 0; i < N; i++) {
        // Exactly one space between each coordinate
        int x1 = inf.readInt(-5000, 5000, "x1");
        inf.readSpace();
        int y1 = inf.readInt(-5000, 5000, "y1");
        inf.readSpace();
        int x2 = inf.readInt(-5000, 5000, "x2");
        inf.readSpace();
        int y2 = inf.readInt(-5000, 5000, "y2");
        inf.readEoln();
        // Note: degenerate (zero-length) segments are allowed by problem statement
    }

    // No extra data
    inf.readEof();
    return 0;
}
