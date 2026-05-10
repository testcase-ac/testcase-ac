#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read image dimensions
    int R = inf.readInt(3, 40, "R");
    inf.readSpace();
    int C = inf.readInt(3, 40, "C");
    inf.readEoln();

    // Read the R×C pixel values
    for (int i = 0; i < R; i++) {
        // Each pixel V must be in [0,255]
        inf.readInts(C, 0, 255, "V");
        inf.readEoln();
    }

    // Read threshold T, also must be in [0,255]
    int T = inf.readInt(0, 255, "T");
    inf.readEoln();

    // No extra data
    inf.readEof();
    return 0;
}
