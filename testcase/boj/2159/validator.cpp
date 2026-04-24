#include "testlib.h"
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of customers
    int n = inf.readInt(1, 100000, "N");
    inf.readEoln();

    // Read starting position (X0, Y0)
    int x0 = inf.readInt(1, 100000, "X0");
    inf.readSpace();
    int y0 = inf.readInt(1, 100000, "Y0");
    inf.readEoln();

    // Read each customer's position
    for (int i = 1; i <= n; i++) {
        char bufX[32], bufY[32];
        sprintf(bufX, "X_%d", i);
        sprintf(bufY, "Y_%d", i);
        int xi = inf.readInt(1, 100000, bufX);
        inf.readSpace();
        int yi = inf.readInt(1, 100000, bufY);
        inf.readEoln();
    }

    // No extra data
    inf.readEof();
    return 0;
}
