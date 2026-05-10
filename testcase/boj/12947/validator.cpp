#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 50, "N");
    inf.readEoln();

    // Read cnt[1..N]
    vector<int> cnt = inf.readInts(N, 1, 1000, "cnt[i]");
    inf.readEoln();

    // No further global constraints are implied by the problem statement.
    // The cnt array is just given, and the solution must construct a tree with the given cnt array.
    // There is no requirement that the input is "possible" or "impossible" -- the solution must handle any input in the given range.

    inf.readEof();
}
