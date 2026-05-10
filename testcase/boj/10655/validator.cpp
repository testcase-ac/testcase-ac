#include "testlib.h"
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(3, 100000, "N");
    inf.readEoln();

    // Read N checkpoint coordinates
    for (int i = 1; i <= N; i++) {
        // x-coordinate
        char name_x[20];
        sprintf(name_x, "x_%d", i);
        int x = inf.readInt(-1000, 1000, name_x);

        inf.readSpace();

        // y-coordinate
        char name_y[20];
        sprintf(name_y, "y_%d", i);
        int y = inf.readInt(-1000, 1000, name_y);

        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
