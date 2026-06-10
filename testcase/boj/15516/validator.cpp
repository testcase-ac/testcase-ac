#include "testlib.h"

#include <set>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "n");
    inf.readEoln();

    set<long long> seen;
    for (int i = 1; i <= n; ++i) {
        long long a = inf.readLong(-2000000000LL, 2000000000LL, "A_i");
        inf.readEoln();

        ensuref(seen.insert(a).second, "A[%d] is not distinct: %lld", i, a);
    }

    inf.readEof();
}
