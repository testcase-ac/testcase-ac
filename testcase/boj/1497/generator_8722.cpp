#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<string> baseNames = {
        "GIBSON", "FENDER", "EPIPHONE", "ESP", "TAYLOR",
        "CRAFTER", "BCRICH", "IBANEZ", "JACKSON", "YAMAHA",
        "MARTIN", "PRS", "GRETSCH", "SCHECTER", "DEAN"
    };

    int scenario = rnd.next(1, 6);

    int N = 0, M = 0;
    vector<string> patterns;

    if (scenario == 1) {
        // Scenario 1: all guitars play no songs -> answer -1
        N = rnd.next(1, 5);
        M = rnd.next(1, 10);
        patterns.assign(N, string(M, 'N'));
    } else if (scenario == 2) {
        // Scenario 2: one dominating guitar can play all songs
        N = rnd.next(1, 8);
        M = rnd.next(1, 20);
        patterns.assign(N, string(M, 'N'));

        int d = rnd.next(0, N - 1); // dominating guitar
        for (int j = 0; j < M; ++j)
            patterns[d][j] = 'Y';

        // Other guitars: random coverage
        for (int i = 0; i < N; ++i) {
            if (i == d) continue;
            for (int j = 0; j < M; ++j) {
                if (rnd.next(0, 99) < 40) // 40% chance of Y
                    patterns[i][j] = 'Y';
            }
        }
    } else if (scenario == 3) {
        // Scenario 3: many guitars each with (at least) one unique song
        N = rnd.next(2, 8);
        M = rnd.next(N, min(20, N + 10));
        patterns.assign(N, string(M, 'N'));

        int K = min(N, M);
        // Make first K guitars each have a unique song
        for (int i = 0; i < K; ++i)
            patterns[i][i] = 'Y';

        // Remaining songs get assigned randomly
        for (int j = K; j < M; ++j) {
            int g = rnd.next(0, N - 1);
            patterns[g][j] = 'Y';
        }

        // Optionally add a few extra Ys to create overlaps
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                if (patterns[i][j] == 'N' && rnd.next(0, 99) < 10) {
                    patterns[i][j] = 'Y';
                }
            }
        }
    } else if (scenario == 4) {
        // Scenario 4: classic tie case where multiple subsets
        // cover the same max songs but with different guitar counts.
        // Based on the sample:
        // 4 5
        // G1 YYYNN
        // G2 YYNNY
        // G3 NNNYY
        // G4 YNNNN
        N = 4;
        M = 5;
        vector<string> base = {
            "YYYNN",
            "YYNNY",
            "NNNYY",
            "YNNNN"
        };

        // Randomly permute songs (columns) to vary layout
        vector<int> perm(M);
        iota(perm.begin(), perm.end(), 0);
        shuffle(perm.begin(), perm.end());

        patterns.assign(N, string(M, 'N'));
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                patterns[i][j] = base[i][perm[j]];
            }
        }
    } else if (scenario == 5) {
        // Scenario 5: random with duplicates and subset relations
        N = rnd.next(3, 10);
        M = rnd.next(3, 18);
        patterns.assign(N, string(M, 'N'));

        // Two base guitars with random patterns, ensure at least one Y each
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < M; ++j) {
                if (rnd.next(0, 99) < 50)
                    patterns[i][j] = 'Y';
            }
            // Ensure at least one Y
            if (count(patterns[i].begin(), patterns[i].end(), 'Y') == 0) {
                int pos = rnd.next(0, M - 1);
                patterns[i][pos] = 'Y';
            }
        }

        // Remaining guitars: duplicates, subsets, or new random patterns
        for (int i = 2; i < N; ++i) {
            int t = rnd.next(0, 2);
            if (t == 0) {
                // Duplicate some previous guitar
                int p = rnd.next(0, i - 1);
                patterns[i] = patterns[p];
            } else if (t == 1) {
                // Subset of some previous guitar
                int p = rnd.next(0, i - 1);
                patterns[i] = patterns[p];
                // Turn at least one Y into N (if any)
                vector<int> ys;
                for (int j = 0; j < M; ++j)
                    if (patterns[i][j] == 'Y') ys.push_back(j);
                if (!ys.empty()) {
                    int removeCnt = rnd.next(1, (int)ys.size());
                    shuffle(ys.begin(), ys.end());
                    for (int k = 0; k < removeCnt; ++k)
                        patterns[i][ys[k]] = 'N';
                }
            } else {
                // Independent random pattern
                for (int j = 0; j < M; ++j) {
                    if (rnd.next(0, 99) < 50)
                        patterns[i][j] = 'Y';
                }
                // Might be all-N; that's fine, adds useless guitars
            }
        }
    } else { // scenario == 6
        // Scenario 6: medium-sized, fairly dense random case
        N = 10;
        M = 25;
        patterns.assign(N, string(M, 'N'));

        int totalY = 0;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                if (rnd.next(0, 99) < 40) {
                    patterns[i][j] = 'Y';
                    ++totalY;
                }
            }
        }
        // Ensure at least one playable song
        if (totalY == 0) {
            patterns[0][0] = 'Y';
        }
    }

    // Assign unique guitar names
    shuffle(baseNames.begin(), baseNames.end());
    vector<string> names;
    for (int i = 0; i < N; ++i)
        names.push_back(baseNames[i]);

    // Output
    println(N, M);
    for (int i = 0; i < N; ++i) {
        println(names[i], patterns[i]);
    }

    return 0;
}
