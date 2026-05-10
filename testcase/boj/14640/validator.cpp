#include "testlib.h"
#include <cassert>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n and t
    int n = inf.readInt(1, 10000, "n");
    inf.readSpace();
    int t = inf.readInt(1, 100000, "t");
    inf.readEoln();

    // Read each time interval
    for (int i = 0; i < n; i++) {
        long long a = inf.readLong(0LL, 1000000000LL, "a_i");
        inf.readSpace();
        long long b = inf.readLong(0LL, 1000000000LL, "b_i");
        inf.readEoln();

        // Validate the constraint a + t <= b
        ensuref(a + t <= b,
                "Invalid time window at photo %d: a + t = %lld > b = %lld",
                i+1, a + t, b);
    }

    // No extra characters after the last newline
    inf.readEof();
    return 0;
}
