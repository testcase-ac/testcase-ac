#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of sticks
    int N = inf.readInt(1, 5000, "N");
    inf.readEoln();

    // Read each stick's endpoints
    for (int i = 0; i < N; i++) {
        int x1 = inf.readInt(0, 10000, "x1");
        inf.readSpace();
        int y1 = inf.readInt(0, 10000, "y1");
        inf.readSpace();
        int x2 = inf.readInt(0, 10000, "x2");
        inf.readSpace();
        int y2 = inf.readInt(0, 10000, "y2");
        inf.readEoln();
    }

    // No extra characters after the last newline
    inf.readEof();
    return 0;
}
