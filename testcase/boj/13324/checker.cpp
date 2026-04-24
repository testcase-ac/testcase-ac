#include "testlib.h"
#include <vector>
#include <climits>
#include <cstdint>
#include <cmath>
using namespace std;

static int N;
static vector<long long> A;

// Reads a candidate sequence B from 'stream', checks that it is strictly increasing
// and within 32-bit signed integer range, computes the cost sum_i |B_i - A_i|.
// On any violation, quits with _wa if stream == ouf, or _fail if stream == ans.
long long readAns(InStream &stream) {
    long long sum = 0;
    // Initialize prev below any valid 32-bit value.
    long long prev = (long long)INT32_MIN - 1;
    for (int i = 0; i < N; i++) {
        long long b = stream.readLong();
        if (b < (long long)INT32_MIN || b > (long long)INT32_MAX) {
            stream.quitf(_wa,
                "B_%d = %lld is out of 32-bit signed integer range", i+1, b);
        }
        if (i > 0 && b <= prev) {
            stream.quitf(_wa,
                "sequence not strictly increasing at index %d: B_%d = %lld, previous = %lld",
                i+1, i+1, b, prev);
        }
        sum += llabs(b - A[i]);
        prev = b;
    }
    // Ensure no extra tokens.
    stream.readEof();
    return sum;
}

int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);

    // Read input
    N = inf.readInt();
    A.resize(N);
    for (int i = 0; i < N; i++) {
        A[i] = inf.readLong();
    }

    // Read jury and participant answers
    long long jans = readAns(ans);
    long long pans = readAns(ouf);

    // Compare costs
    if (pans > jans) {
        quitf(_wa,
              "contestant's sum = %lld is larger than jury's minimal sum = %lld",
              pans, jans);
    } else if (pans < jans) {
        // Participant found a strictly better cost => jury is wrong
        quitf(_fail,
              "contestant's sum = %lld is smaller than jury's = %lld",
              pans, jans);
    } else {
        quitf(_ok, "minimal sum = %lld", pans);
    }
}
