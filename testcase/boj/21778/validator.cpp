#include "testlib.h"

#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const long long kMaxValue = 1000000000000LL;
    const long long kMaxQueryTime = 100000000000000000LL;

    int q = inf.readInt(1, 50, "Q");
    inf.readSpace();
    int n = inf.readInt(1, 100000, "n");
    inf.readEoln();

    set<long long> ids;
    __int128 totalTime = 0;
    for (int i = 0; i < n; ++i) {
        long long a = inf.readLong(1LL, kMaxValue, "A_i");
        inf.readSpace();
        long long b = inf.readLong(1LL, kMaxValue, "B_i");
        inf.readSpace();
        inf.readLong(1LL, kMaxValue, "C_i");
        inf.readEoln();

        // CHECK: The statement uses A_i as a process id; duplicate ids make the
        // scheduler's selected process identifier ambiguous.
        ensuref(ids.insert(a).second, "duplicate process id at row %d: %lld", i + 1, a);
        totalTime += b;
    }

    long long maxAllowedQuery = kMaxQueryTime;
    if (totalTime < maxAllowedQuery) {
        maxAllowedQuery = (long long)totalTime;
    }

    for (int i = 0; i < q; ++i) {
        inf.readLong(1LL, maxAllowedQuery, "T_c");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
