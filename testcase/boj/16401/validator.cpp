#include "testlib.h"
#include <vector>
#include <algorithm>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read M and N
    int M = inf.readInt(1, 1000000, "M");
    inf.readSpace();
    int N = inf.readInt(1, 1000000, "N");
    inf.readEoln();

    // Read N integers: L_1 ... L_N
    vector<int> L = inf.readInts(N, 1, 1000000000, "L_i");
    inf.readEoln();

    // No further global constraints to check (e.g., no guarantee that answer exists, so no need to check that).
    // No further formatting (no more lines).

    inf.readEof();
}
