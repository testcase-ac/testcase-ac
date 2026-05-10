#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int winnerOfTwo(char a, char b) {
    if (a == b) return 0; // draw
    if (a == 'R' && b == 'S') return 1;
    if (a == 'S' && b == 'P') return 1;
    if (a == 'P' && b == 'R') return 1;
    return 2;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        int N = inf.readInt(2, 10, "N");
        inf.readEoln();

        vector<string> s(N);
        int k = -1;

        for (int i = 0; i < N; ++i) {
            s[i] = inf.readToken("[RPS]+", "robot_string");
            inf.readEoln();

            if (k == -1) {
                k = (int)s[i].size();
                ensuref(3 <= k && k <= 30, "k (length of strings) must be in [3,30], got %d", k);
            } else {
                ensuref((int)s[i].size() == k,
                        "All strings must have the same length k, expected %d, got %d at robot %d",
                        k, (int)s[i].size(), i + 1);
            }
        }

        // Simulate the tournament to ensure the described behavior is always possible.
        vector<int> alive(N, 1);

        for (int round = 0; round < k; ++round) {
            vector<int> aliveIdx;
            for (int i = 0; i < N; ++i)
                if (alive[i]) aliveIdx.push_back(i);

            if ((int)aliveIdx.size() <= 1) break;

            // Count moves among alive robots this round
            bool hasR = false, hasP = false, hasS = false;
            for (int idx : aliveIdx) {
                char c = s[idx][round];
                if (c == 'R') hasR = true;
                else if (c == 'P') hasP = true;
                else if (c == 'S') hasS = true;
            }

            // Determine which moves win/lose
            // Cases:
            // - Single type present: all draw, no elimination.
            // - Two types present: one type beats the other, losers eliminated.
            // - Three types present: they form a cycle, all draw, no elimination.
            int types = (int)hasR + (int)hasP + (int)hasS;

            if (types == 2) {
                char winnerMove = 0, loserMove = 0;
                if (hasR && hasS) { winnerMove = 'R'; loserMove = 'S'; }
                else if (hasS && hasP) { winnerMove = 'S'; loserMove = 'P'; }
                else if (hasP && hasR) { winnerMove = 'P'; loserMove = 'R'; }
                else {
                    ensuref(false, "Unexpected move combination logic error");
                }

                // Eliminate robots with loserMove
                for (int i = 0; i < N; ++i) {
                    if (alive[i] && s[i][round] == loserMove)
                        alive[i] = 0;
                }
            }
            // types == 1 or 3: no eliminations this round
        }

        // Count survivors and deduce the official winner according to the rules.
        int winnerIdx = -1;
        int aliveCount = 0;
        for (int i = 0; i < N; ++i) {
            if (alive[i]) {
                ++aliveCount;
                winnerIdx = i;
            }
        }
        int computedAnswer = (aliveCount == 1 ? winnerIdx + 1 : 0);

        // There is no explicit "answer always exists" or upper bound property
        // beyond this rule, so no further global constraints to check.

        // No output from validator.

    }

    inf.readEof();
}
