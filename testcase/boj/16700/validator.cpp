#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of operations
    int L = inf.readInt(1, 200000, "L");
    inf.readEoln();

    // Each operation: t, x1, y1, x2, y2
    for (int i = 0; i < L; i++) {
        int t = inf.readInt(0, 1, "t");
        inf.readSpace();
        int x1 = inf.readInt(1, 50, "x1");
        inf.readSpace();
        int y1 = inf.readInt(1, 100000, "y1");
        inf.readSpace();
        int x2 = inf.readInt(1, 50, "x2");
        inf.readSpace();
        int y2 = inf.readInt(1, 100000, "y2");
        inf.readEoln();

        // No further constraints on ordering of x1,x2 or y1,y2 since they are opposite corners
        // No additional global assumptions (e.g., connectivity) to validate here
    }

    inf.readEof();
    return 0;
}
