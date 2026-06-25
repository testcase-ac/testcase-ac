#include "testlib.h"

#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The input section omits an explicit upper bound for N; the subtask
    // table defines the full problem range as 0 <= N <= 4000.
    int n = inf.readInt(0, 4000, "N");
    inf.readEoln();

    vector<int> f = inf.readInts(n + 1, 0, 1000000006, "f_i");
    inf.readEoln();

    if (n >= 1) {
        ensuref(f[n] != 0, "f_N must be nonzero when N >= 1");
    }

    inf.readEof();
}
