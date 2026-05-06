#include "testlib.h"
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and K
    int N = inf.readInt(1, 1000, "N");
    inf.readSpace();
    int K = inf.readInt(1, 1000, "K");
    inf.readEoln();

    // Read a_i
    vector<int> a = inf.readInts(N, 1, 1000, "a_i");
    inf.readEoln();

    // Check that a_i are all positive and in range (already checked by readInts)
    // No further constraints on a_i (duplicates allowed)

    inf.readEof();
}
