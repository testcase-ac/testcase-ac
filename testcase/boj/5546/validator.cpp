#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(3, 100, "N");
    inf.readSpace();
    int k = inf.readInt(1, n, "K");
    inf.readEoln();

    vector<int> fixed(n + 1, 0);
    vector<bool> seen(n + 1, false);
    for (int i = 1; i <= k; ++i) {
        int day = inf.readInt(1, n, "A_i");
        inf.readSpace();
        int pasta = inf.readInt(1, 3, "B_i");
        inf.readEoln();

        ensuref(!seen[day], "A_i values must be distinct, duplicate day %d", day);
        seen[day] = true;
        fixed[day] = pasta;
    }

    vector<vector<int>> dp(4, vector<int>(3, 0));
    for (int pasta = 1; pasta <= 3; ++pasta) {
        if (fixed[1] == 0 || fixed[1] == pasta) {
            dp[pasta][1] = 1;
        }
    }

    for (int day = 2; day <= n; ++day) {
        vector<vector<int>> next(4, vector<int>(3, 0));
        for (int prev = 1; prev <= 3; ++prev) {
            for (int streak = 1; streak <= 2; ++streak) {
                if (dp[prev][streak] == 0) {
                    continue;
                }
                for (int pasta = 1; pasta <= 3; ++pasta) {
                    if (fixed[day] != 0 && fixed[day] != pasta) {
                        continue;
                    }
                    int nextStreak = (pasta == prev) ? streak + 1 : 1;
                    if (nextStreak <= 2) {
                        next[pasta][nextStreak] = 1;
                    }
                }
            }
        }
        dp = next;
    }

    bool feasible = false;
    for (int pasta = 1; pasta <= 3; ++pasta) {
        for (int streak = 1; streak <= 2; ++streak) {
            feasible = feasible || dp[pasta][streak] != 0;
        }
    }
    ensuref(feasible, "the original statement guarantees at least one valid plan");

    inf.readEof();
}
