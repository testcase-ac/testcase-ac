#include "testlib.h"
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 30000, "N");
    inf.readEoln();

    // Read each vector
    for (int i = 1; i <= N; i++) {
        // x coordinate
        char nameX[20];
        std::sprintf(nameX, "x_%d", i);
        int x = inf.readInt(-30000, 30000, nameX);
        inf.readSpace();
        // y coordinate
        char nameY[20];
        std::sprintf(nameY, "y_%d", i);
        int y = inf.readInt(-30000, 30000, nameY);
        inf.readEoln();

        // Ensure not zero vector
        ensuref(x != 0 || y != 0,
                "Vector at index %d is (0,0), which is not allowed", i);
    }

    inf.readEof();
    return 0;
}
