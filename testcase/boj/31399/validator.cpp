#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read H, W
    int H = inf.readInt(1, 1024, "H");
    inf.readSpace();
    int W = inf.readInt(1, 1024, "W");
    inf.readEoln();

    // 2. Read R, C, D
    int R = inf.readInt(0, H - 1, "R");
    inf.readSpace();
    int C = inf.readInt(0, W - 1, "C");
    inf.readSpace();
    int D = inf.readInt(0, 3, "D");
    inf.readEoln();

    // 3. Read A (H lines of W digits, each in [0,3])
    vector<string> A(H);
    for (int i = 0; i < H; ++i) {
        A[i] = inf.readLine("[0-3]{" + vtos(W) + "}", "A[i]");
        ensuref((int)A[i].size() == W, "Line %d of A has length %d, expected %d", i+1, (int)A[i].size(), W);
    }

    // 4. Read B (H lines of W digits, each in [0,3])
    vector<string> B(H);
    for (int i = 0; i < H; ++i) {
        B[i] = inf.readLine("[0-3]{" + vtos(W) + "}", "B[i]");
        ensuref((int)B[i].size() == W, "Line %d of B has length %d, expected %d", i+1, (int)B[i].size(), W);
    }

    // 5. Ensure EOF
    inf.readEof();
}
