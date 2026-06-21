#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int missingTeam = inf.readInt(1, 4, "T");
    inf.readSpace();
    long long k = inf.readLong(1000LL, 1000000000000LL, "K");
    inf.readEoln();

    int missingCount = 0;
    int missingRow = -1;
    for (int i = 1; i <= 4; ++i) {
        for (int j = 1; j <= 4; ++j) {
            long long score = inf.readLong(-1LL, k, "W_ij");
            if (j < 4) {
                inf.readSpace();
            } else {
                inf.readEoln();
            }

            if (i == j) {
                ensuref(score == 0, "diagonal score W_%d%d must be 0, got %lld", i, j, score);
            } else if (score == -1) {
                ++missingCount;
                missingRow = i;
            }
        }
    }

    ensuref(missingCount == 1, "expected exactly one missing score, got %d", missingCount);
    ensuref(missingRow == missingTeam, "missing score row must be T=%d, got row %d", missingTeam, missingRow);

    inf.readEof();
}
