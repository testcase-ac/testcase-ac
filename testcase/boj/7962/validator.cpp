#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const long long LIMIT = 2000000000LL;

    int n = inf.readInt(3, 1000000, "N");
    inf.readEoln();

    long long totalFuel = 0;
    long long totalDistance = 0;
    for (int i = 1; i <= n; ++i) {
        // CHECK: The English statement says p_i <= 0, but the sample and problem
        // meaning require available fuel amounts to be nonnegative.
        long long p = inf.readLong(0LL, LIMIT, "p_i");
        inf.readSpace();
        long long d = inf.readLong(1LL, LIMIT, "d_i");
        inf.readEoln();

        totalFuel += p;
        totalDistance += d;
        ensuref(totalFuel <= LIMIT,
                "total fuel exceeds 2000000000 after station %d", i);
        ensuref(totalDistance <= LIMIT,
                "total distance exceeds 2000000000 after station %d", i);
    }

    inf.readEof();
    return 0;
}
