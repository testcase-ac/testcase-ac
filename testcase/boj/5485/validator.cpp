#include "testlib.h"
#include <cstdint>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read and validate n
    int n = inf.readInt(2, 5000000, "n");
    inf.readEoln();

    // Read the sequence m_1 ... m_n, ensure each is in [0,1e9]
    // and ensure it's non-decreasing.
    long long prev = -1;
    for (int i = 1; i <= n; ++i) {
        long long m = inf.readLong(0LL, 1000000000LL, "m_i");
        inf.readEoln();
        if (i > 1) {
            ensuref(m >= prev,
                    "m[%d] = %lld is less than previous m[%d] = %lld", 
                    i, m, i-1, prev);
        }
        prev = m;
    }

    // No extra data
    inf.readEof();
    return 0;
}
