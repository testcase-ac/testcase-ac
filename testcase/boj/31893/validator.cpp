#include "testlib.h"
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n and c
    int n = inf.readInt(2, 10000, "n");
    inf.readSpace();
    int c = inf.readInt(2, 10000, "c");
    inf.readEoln();

    // Read t_1..t_n
    vector<int> t = inf.readInts(n, 1, 1000000000, "t_i");
    inf.readEoln();

    // Check for duplicate walkers with same crossing time is NOT required (not specified)
    // Check for global properties:

    // 1. All walkers must cross, and only c walkers can cross at a time.
    // 2. There is only one torch, so at least one walker must return with the torch if not all have crossed.
    // 3. The problem guarantees that the answer always exists, but does not require us to check for any other global property.

    // No further global validation is required, as all constraints are covered.

    inf.readEof();
}
