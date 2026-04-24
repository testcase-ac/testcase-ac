#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read H and T
    int H = inf.readInt(1, 100000, "H");
    inf.readSpace();
    int T = inf.readInt(1, 16, "T");
    inf.readEoln();

    // Read C_k for each day
    vector<int> C = inf.readInts(H, 0, 100000, "C_k");
    inf.readEoln();

    // Read team descriptions
    for (int t = 1; t <= T; t++) {
        int D = inf.readInt(1, H, "D_t");
        inf.readSpace();
        int I = inf.readInt(0, 1000000, "I_t");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
