#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read first line: N, B, C
    int N = inf.readInt(3, 1000000, "N");
    inf.readSpace();
    int B = inf.readInt(1, 1000000, "B");
    inf.readSpace();
    int C = inf.readInt(1, 1000000, "C");
    inf.readEoln();

    // Read second line: A1 ... AN
    // Each Ai: 0 <= Ai <= 1e6
    inf.readInts(N, 0, 1000000, "A_i");
    inf.readEoln();

    inf.readEof();
    return 0;
}
