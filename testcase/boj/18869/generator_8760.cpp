#include "testlib.h"
using namespace std;

vector<int> makeUniverseFromPattern(const vector<int>& rankPattern) {
    int maxRank = 0;
    for (int r : rankPattern) if (r > maxRank) maxRank = r;
    int K = maxRank + 1;

    vector<int> base(K);
    base[0] = rnd.next(1, 10);
    for (int k = 1; k < K; ++k) {
        base[k] = base[k - 1] + rnd.next(1, 5);
    }

    vector<int> res(rankPattern.size());
    for (int i = 0; i < (int)rankPattern.size(); ++i) {
        res[i] = base[rankPattern[i]];
    }
    return res;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int scenario = rnd.next(0, 3); // 0,1,2,3
    int M, N;
    vector<vector<int>> universes;

    if (scenario == 0) {
        // Multiple random equivalence classes
        N = rnd.next(3, 8);
        M = rnd.next(2, 7);
        universes.assign(M, vector<int>(N));

        int P = rnd.next(1, min(3, M)); // number of distinct patterns
        vector<vector<int>> basePatterns(P, vector<int>(N));

        for (int p = 0; p < P; ++p) {
            int K = rnd.next(1, min(3, N)); // number of distinct ranks in this pattern
            // random initial pattern
            for (int i = 0; i < N; ++i)
                basePatterns[p][i] = rnd.next(0, K - 1);

            // ensure every rank 0..K-1 appears at least once
            for (int r = 0; r < K; ++r) {
                bool found = false;
                for (int i = 0; i < N; ++i)
                    if (basePatterns[p][i] == r) { found = true; break; }
                if (!found) {
                    int pos = rnd.next(0, N - 1);
                    basePatterns[p][pos] = r;
                }
            }
        }

        vector<int> patIdx(M);
        patIdx[0] = 0;
        if (M > 1) patIdx[1] = 0; // guarantee at least one equal pair
        for (int i = 2; i < M; ++i)
            patIdx[i] = rnd.next(0, P - 1);

        for (int u = 0; u < M; ++u) {
            universes[u] = makeUniverseFromPattern(basePatterns[patIdx[u]]);
        }

    } else if (scenario == 1) {
        // Sorting-trap scenario
        N = rnd.next(4, 8);
        M = rnd.next(3, 7);
        universes.assign(M, vector<int>(N));

        // Create a base pattern with at least one descent
        vector<int> pattern0(N);
        int K0 = rnd.next(2, min(3, N));
        for (int i = 0; i < N; ++i)
            pattern0[i] = rnd.next(0, K0 - 1);

        // Ensure all ranks appear
        for (int r = 0; r < K0; ++r) {
            bool found = false;
            for (int i = 0; i < N; ++i)
                if (pattern0[i] == r) { found = true; break; }
            if (!found) {
                int pos = rnd.next(0, N - 1);
                pattern0[pos] = r;
            }
        }

        // Ensure pattern is not nondecreasing (create at least one descent)
        bool nondec = true;
        for (int i = 1; i < N; ++i)
            if (pattern0[i] < pattern0[i - 1]) { nondec = false; break; }
        if (nondec && K0 > 1) {
            int x = 0, y = -1;
            for (int i = 1; i < N; ++i) {
                if (pattern0[i] != pattern0[x]) { y = i; break; }
            }
            if (y != -1) {
                swap(pattern0[x], pattern0[y]);
            }
        }

        // Universe 0 and 1: equal by specification (same pattern, different monotone mapping)
        universes[0] = makeUniverseFromPattern(pattern0);
        universes[1] = makeUniverseFromPattern(pattern0);

        // Universe 2: sorted version of universe 0 (same multiset, generally not equal by spec)
        vector<int> tmp = universes[0];
        sort(tmp.begin(), tmp.end());
        universes[2] = tmp;

        // Remaining universes: random patterns
        for (int u = 3; u < M; ++u) {
            int K = rnd.next(1, min(3, N));
            vector<int> pat(N);
            for (int i = 0; i < N; ++i)
                pat[i] = rnd.next(0, K - 1);
            // ensure all ranks appear
            for (int r = 0; r < K; ++r) {
                bool found = false;
                for (int i = 0; i < N; ++i)
                    if (pat[i] == r) { found = true; break; }
                if (!found) {
                    int pos = rnd.next(0, N - 1);
                    pat[pos] = r;
                }
            }
            universes[u] = makeUniverseFromPattern(pat);
        }

    } else if (scenario == 2) {
        // Mix of all-equal universes and two-level universes
        N = rnd.next(3, 8);
        M = rnd.next(2, 7);
        universes.assign(M, vector<int>(N));

        // All-equal pattern
        vector<int> allEqual(N, 0);
        // Two-level pattern: first part 0, second part 1
        vector<int> twoLevel(N);
        int split = rnd.next(1, N - 1);
        for (int i = 0; i < N; ++i)
            twoLevel[i] = (i < split ? 0 : 1);

        universes[0] = makeUniverseFromPattern(allEqual);
        if (M > 1) universes[1] = makeUniverseFromPattern(allEqual); // at least one equal pair of all-equal

        for (int u = 2; u < M; ++u) {
            int choice = rnd.next(0, 2);
            if (choice == 0) {
                universes[u] = makeUniverseFromPattern(allEqual);
            } else {
                // sometimes reverse the two-level pattern
                vector<int> pat = twoLevel;
                if (rnd.next(0, 1)) {
                    reverse(pat.begin(), pat.end());
                }
                universes[u] = makeUniverseFromPattern(pat);
            }
        }

    } else {
        // Alternating pattern and variations
        N = rnd.next(4, 8);
        M = rnd.next(3, 7);
        universes.assign(M, vector<int>(N));

        vector<int> alt(N);
        for (int i = 0; i < N; ++i)
            alt[i] = i % 2; // 0,1,0,1,...

        vector<int> altRev = alt;
        reverse(altRev.begin(), altRev.end());

        universes[0] = makeUniverseFromPattern(alt);
        if (M > 1) universes[1] = makeUniverseFromPattern(alt); // equal pair

        if (M > 2) universes[2] = makeUniverseFromPattern(altRev); // different pattern

        for (int u = 3; u < M; ++u) {
            int t = rnd.next(0, 2);
            if (t == 0) {
                universes[u] = makeUniverseFromPattern(alt);
            } else if (t == 1) {
                universes[u] = makeUniverseFromPattern(altRev);
            } else {
                // small random pattern with 3 ranks
                int K = 3;
                vector<int> pat(N);
                for (int i = 0; i < N; ++i)
                    pat[i] = rnd.next(0, K - 1);
                // ensure all ranks appear
                for (int r = 0; r < K; ++r) {
                    bool found = false;
                    for (int i = 0; i < N; ++i)
                        if (pat[i] == r) { found = true; break; }
                    if (!found) {
                        int pos = rnd.next(0, N - 1);
                        pat[pos] = r;
                    }
                }
                universes[u] = makeUniverseFromPattern(pat);
            }
        }
    }

    println(M, N);
    for (int i = 0; i < M; ++i)
        println(universes[i]);

    return 0;
}
