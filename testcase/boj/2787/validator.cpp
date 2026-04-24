#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(1, 200, "N");
    inf.readSpace();
    int M = inf.readInt(0, 40000, "M");
    inf.readEoln();

    // Read M descriptions
    for (int i = 0; i < M; i++) {
        int t = inf.readInt(1, 2, "type");
        inf.readSpace();
        int x = inf.readInt(1, N, "x");
        inf.readSpace();
        int y = inf.readInt(1, N, "y");
        inf.readSpace();
        int v = inf.readInt(1, N, "v");
        inf.readEoln();

        ensuref(x <= y,
                "In query %d: x (%d) must be <= y (%d)", i+1, x, y);
        // For type 1 or 2, v is within [1, N], already enforced
    }

    inf.readEof();
    return 0;
}
