#include "testlib.h"
#include <vector>
#include <algorithm>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 300000, "N");
    inf.readEoln();

    // Read N integers Ai, each 0 or 1
    vector<int> a = inf.readInts(N, 0, 1, "A_i");
    inf.readEoln();

    // No further global constraints to validate:
    // - Cards are independent binary states; no connectivity / polygon / etc.
    // - Problem doesn't guarantee existence/limit of answer beyond trivial (1..N),
    //   and that follows directly from N, so no need to recompute and check.

    inf.readEof();
}
