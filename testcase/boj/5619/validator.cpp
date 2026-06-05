#include "testlib.h"

#include <set>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The statement writes n <= 10^8, but also requires n distinct
    // values in [1, 10000], so n > 10000 cannot form a valid input.
    int n = inf.readInt(3, 10000, "n");
    inf.readEoln();

    set<int> seen;
    for (int i = 1; i <= n; ++i) {
        int a = inf.readInt(1, 10000, "a_i");
        inf.readEoln();

        ensuref(seen.insert(a).second, "duplicate a_i at index %d: %d", i, a);
    }

    inf.readEof();
}
