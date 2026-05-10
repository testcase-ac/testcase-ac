#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N, A, B
    int N = inf.readInt(1, 100, "N");
    inf.readSpace();
    int A = inf.readInt(1, 100, "A");
    inf.readSpace();
    int B = inf.readInt(1, 100, "B");
    inf.readEoln();

    // Read T_1 ... T_N
    vector<int> T = inf.readInts(N, 1, 10000, "T_i");
    inf.readEoln();

    // No further constraints in the statement:
    // - T_i can be equal (no uniqueness required)
    // - No global properties to check (e.g., answer always exists, etc.)
    // - All numbers are integers, already checked by readInts

    inf.readEof();
}
