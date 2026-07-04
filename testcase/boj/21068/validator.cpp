#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 10000, "t");
    inf.readEoln();

    long long totalN = 0;
    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, 1000000, "n");
        inf.readEoln();
        totalN += n;
        ensuref(totalN <= 1000000LL, "sum of n exceeds 1000000");

        vector<long long> a = inf.readLongs(n, 0LL, 1000000000LL, "a_i");
        inf.readEoln();
        vector<long long> b = inf.readLongs(n, 0LL, 1000000000LL, "b_i");
        inf.readEoln();

        long long totalDraws = 0;
        long long maxDraws = 0;
        long long totalWins = 0;
        for (int i = 0; i < n; ++i) {
            long long wins = b[i] - a[i];
            long long draws = 3 * a[i] - 2 * b[i];

            ensuref(wins >= 0, "player %d has negative win count", i);
            ensuref(draws >= 0, "player %d has negative draw count", i);

            totalWins += wins;
            totalDraws += draws;
            if (draws > maxDraws) {
                maxDraws = draws;
            }
        }

        if (n == 1) {
            ensuref(totalWins == 0, "single-player tournament cannot contain wins");
            ensuref(totalDraws == 0, "single-player tournament cannot contain draws");
        } else {
            ensuref(totalDraws % 2 == 0, "total draw count must be even");
            ensuref(maxDraws <= totalDraws - maxDraws,
                    "draw counts cannot be realized without self-pairing");
        }
    }

    inf.readEof();
}
