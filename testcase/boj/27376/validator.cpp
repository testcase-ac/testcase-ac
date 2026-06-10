#include "testlib.h"

#include <set>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MAX_K = 100000;

    long long n = inf.readLong(1LL, 1000000000LL, "n");
    inf.readSpace();
    int k = inf.readInt(0, min<long long>(MAX_K, n - 1), "k");
    inf.readEoln();

    set<long long> positions;
    for (int i = 1; i <= k; ++i) {
        long long x = inf.readLong(1LL, n - 1, "x_i");
        inf.readSpace();
        long long t = inf.readLong(1LL, 1000000000LL, "t_i");
        inf.readSpace();
        long long s = inf.readLong(0LL, t - 1, "s_i");
        inf.readEoln();

        ensuref(positions.insert(x).second,
                "duplicate traffic light position at line %d: %lld",
                i + 1,
                x);
    }

    inf.readEof();
    return 0;
}
