#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of points N
    int N = inf.readInt(2, 50000, "N");
    inf.readEoln();

    // Read N distances and ensure total sum <= 1e9
    long long total = 0;
    for (int i = 1; i <= N; i++) {
        long long d = inf.readLong(1LL, 1000000000LL, "d_i");
        total += d;
        ensuref(total <= 1000000000LL,
                "Total distance sum exceeds 1e9 after reading d_%d: sum=%lld", i, total);
        inf.readEoln();
    }

    // No extra data allowed
    inf.readEof();
    return 0;
}
