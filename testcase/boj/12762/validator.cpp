#include "testlib.h"
#include <vector>
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read N
    int N = inf.readInt(1, 1000, "N");
    inf.readEoln();

    // 2. Read heights
    vector<int> h = inf.readInts(N, 1, 10000, "h_i");
    inf.readEoln();

    // 3. No further constraints in statement (no global property to check).
    //    - No requirement for distinct heights.
    //    - No requirement for highlight section to always exist (the solution handles that).
    //    - No further structure to check.

    inf.readEof();
}
