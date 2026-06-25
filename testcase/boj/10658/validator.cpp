#include "testlib.h"

#include <set>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 50000, "n");
    inf.readSpace();
    long long a = inf.readLong(1LL, 1000000000LL, "a");
    inf.readSpace();
    long long b = inf.readLong(a, 1000000000LL, "b");
    inf.readEoln();

    set<long long> weights;
    for (int i = 0; i < n; ++i) {
        string spotted = inf.readToken("S|NS", "spotted");
        inf.readSpace();
        long long w = inf.readLong(1LL, 1000000000LL, "w");
        inf.readEoln();

        ensuref(weights.insert(w).second,
                "cow weights must be distinct, duplicate weight %lld at cow %d",
                w, i + 1);
        (void)spotted;
    }

    inf.readEof();
}
