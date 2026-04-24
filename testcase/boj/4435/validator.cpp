#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of battles
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    // Weights for each race
    const int goodW[6] = {1, 2, 3, 3, 4, 10};
    const int evilW[7] = {1, 2, 2, 2, 3, 5, 10};
    const long long INT32_MAX_LL = 2147483647LL;

    for (int tc = 1; tc <= T; tc++) {
        setTestCase(tc);

        // Read Gandalf's army counts: 6 non-negative integers
        vector<long long> good = inf.readLongs(6, 0LL, INT32_MAX_LL, "good_i");
        inf.readEoln();

        // Read Sauron's army counts: 7 non-negative integers
        vector<long long> evil = inf.readLongs(7, 0LL, INT32_MAX_LL, "evil_i");
        inf.readEoln();

        // Compute and validate the total scores fit in 32-bit signed int
        __int128 sumGood = 0;
        for (int i = 0; i < 6; i++) {
            sumGood += (__int128)good[i] * goodW[i];
        }
        ensuref(sumGood <= INT32_MAX_LL,
                "Score of Good in battle %d is %lld, exceeds 32-bit limit",
                tc, (long long)sumGood);

        __int128 sumEvil = 0;
        for (int i = 0; i < 7; i++) {
            sumEvil += (__int128)evil[i] * evilW[i];
        }
        ensuref(sumEvil <= INT32_MAX_LL,
                "Score of Evil in battle %d is %lld, exceeds 32-bit limit",
                tc, (long long)sumEvil);
    }

    inf.readEof();
    return 0;
}
