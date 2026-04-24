#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; ++tc) {
        // Read H, W, N
        int H = inf.readInt(1, 99, "H");
        inf.readSpace();
        int W = inf.readInt(1, 99, "W");
        inf.readSpace();
        // N must satisfy 1 <= N <= H * W
        int maxRooms = H * W;
        int N = inf.readInt(1, maxRooms, "N");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
