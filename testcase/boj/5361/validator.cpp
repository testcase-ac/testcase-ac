#include "testlib.h"
#include <cstdint>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of test cases: assume at least 1, at most 100000
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    // Prices in cents
    const int64_t P_A = 35034;  // Blaster rifle
    const int64_t P_B = 23090;  // Vision sensor
    const int64_t P_C = 19055;  // Audio sensor
    const int64_t P_D = 12530;  // Arm
    const int64_t P_E = 18090;  // Leg
    // Max total cost in cents = 1e8 dollars * 100
    const __int128 MAX_CENTS = (__int128)100000000 * 100;

    for (int i = 0; i < T; i++) {
        // Read five non-negative integers A, B, C, D, E
        char buf[32];

        sprintf(buf, "A_%d", i);
        int64_t A = inf.readLong(0, 100000000LL, buf);
        inf.readSpace();

        sprintf(buf, "B_%d", i);
        int64_t B = inf.readLong(0, 100000000LL, buf);
        inf.readSpace();

        sprintf(buf, "C_%d", i);
        int64_t C = inf.readLong(0, 100000000LL, buf);
        inf.readSpace();

        sprintf(buf, "D_%d", i);
        int64_t D = inf.readLong(0, 100000000LL, buf);
        inf.readSpace();

        sprintf(buf, "E_%d", i);
        int64_t E = inf.readLong(0, 100000000LL, buf);
        inf.readEoln();

        // Compute total cost in cents using 128-bit to avoid overflow
        __int128 total = (__int128)A * P_A
                       + (__int128)B * P_B
                       + (__int128)C * P_C
                       + (__int128)D * P_D
                       + (__int128)E * P_E;

        // Validate the problem guarantee: total cost <= 1e8 dollars
        ensuref(total <= MAX_CENTS,
                "Total cost for test %d exceeds $100,000,000: got cents = %lld",
                i, (long long)total);
    }

    inf.readEof();
    return 0;
}
