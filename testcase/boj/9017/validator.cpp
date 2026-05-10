#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // T: number of test cases, not specified upper bound in statement,
    // so assume up to 100000 as per instructions.
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 0; tc < T; ++tc) {
        setTestCase(tc + 1);

        int N = inf.readInt(6, 1000, "N");
        inf.readEoln();

        // Read team numbers
        vector<int> t = inf.readInts(N, 1, 200, "t_i");
        inf.readEoln();

        // Global consistency checks implied by the problem.

        // 1. Each team has at most 6 runners.
        // 2. At least one team has exactly 6 runners.
        vector<int> cnt(201, 0); // team numbers are 1..M, M<=200
        for (int i = 0; i < N; ++i) {
            int id = t[i];
            ensuref(1 <= id && id <= 200, "team id t_%d=%d out of [1,200]", i + 1, id);
            cnt[id]++;
        }

        bool hasExactlySix = false;
        for (int id = 1; id <= 200; ++id) {
            ensuref(cnt[id] <= 6, "team %d has %d runners (>6)", id, cnt[id]);
            if (cnt[id] == 6) hasExactlySix = true;
        }
        ensuref(hasExactlySix, "no team with exactly 6 runners in test case %d", tc + 1);

        // 3. (Optional but useful sanity) Simulate scoring and ensure a unique winner exists.
        // Only teams with exactly 6 runners are considered.
        const int MAX_TEAM = 200;
        vector<int> score(MAX_TEAM + 1, 0);
        vector<int> fifthScore(MAX_TEAM + 1, 0);
        vector<int> finishCount(MAX_TEAM + 1, 0);

        // We assign scores only to teams with exactly 6 runners.
        for (int pos = 0; pos < N; ++pos) {
            int team = t[pos];
            if (cnt[team] != 6) continue; // not a qualified team, skip scoring

            int rankScore = pos + 1; // positions are 1-based in scoring
            int fc = ++finishCount[team];

            if (fc <= 4) {
                score[team] += rankScore;
            }
            if (fc == 5) {
                fifthScore[team] = rankScore;
            }
        }

        int bestTeam = -1;
        int bestScore = INT_MAX;
        int bestFifth = INT_MAX;

        for (int id = 1; id <= MAX_TEAM; ++id) {
            if (cnt[id] == 6) {
                // By rules, a qualified team must have at least 5 finish counts.
                // However, N can be larger due to other teams, but within a team it's exactly 6.
                ensuref(finishCount[id] == 6,
                        "qualified team %d with 6 runners has finishCount=%d (must be 6)",
                        id, finishCount[id]);

                if (score[id] < bestScore ||
                    (score[id] == bestScore && fifthScore[id] < bestFifth)) {
                    bestScore = score[id];
                    bestFifth = fifthScore[id];
                    bestTeam = id;
                }
            }
        }

        ensuref(bestTeam != -1, "no winner team found in test case %d", tc + 1);
    }

    inf.readEof();
}
