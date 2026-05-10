#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

// Safely add two long long using __int128 for overflow check if desired
inline long long addll(long long a, long long b) {
    __int128 s = ( __int128)a + ( __int128)b;
    return (long long)s;
}

// Compute for one test case the answers described in the statement, to
// verify any global guarantees if needed (here we just ensure results
// fit in 64-bit signed range).
void checkAnswers(int n, const vector<pair<int,int>>& edges) {
    int m = (int)edges.size();
    int other = n - 2; // players except captains 1 and 2

    // Precompute adjacency bitmasks for players 3..n
    int k = max(0, other);
    if (k > 24) {
        // For large n (hard subtask), computing exact optimum is expensive.
        // The statement does not give global properties we must enforce
        // (like "answer always <= X"), beyond trivial integer bounds.
        // We'll only check that simple theoretical bounds are within 64-bit.
        long long maxPairs = 1LL * n * (n - 1) / 2;
        // Strength is #edges inside each team, max <= m, and sum <= m
        // but m <= maxPairs, and maxPairs for n<=200 fits in 64-bit safely.
        ensuref(maxPairs <= (long long)4e4, "Internal bound sanity failed");
        return;
    }

    // Map players 3..n to bits 0..k-1
    vector<int> id(n + 1, -1);
    for (int v = 3, b = 0; v <= n; ++v, ++b) id[v] = b;

    // For each vertex (including captains) build bitmask of neighbors among 3..n
    vector<int> mask(n + 1, 0);
    for (auto e : edges) {
        int u = e.first;
        int v = e.second;
        if (u >= 3 && v >= 3) {
            int bu = id[u], bv = id[v];
            mask[u] |= (1 << bv);
            mask[v] |= (1 << bu);
        } else if (u >= 3 && v <= 2) {
            int bu = id[u];
            mask[v] |= (1 << bu);
        } else if (v >= 3 && u <= 2) {
            int bv = id[v];
            mask[u] |= (1 << bv);
        }
    }

    long long bestSum = 0;
    long long bestDiff = (1LL << 60);

    int totalSub = (k == 0) ? 1 : (1 << k);
    for (int s = 0; s < totalSub; ++s) {
        // Partition:
        // Team A has captain 1; Team B has captain 2.
        // Bit b of s: 0 -> goes with 1, 1 -> goes with 2.

        long long SA = 0, SB = 0; // strengths
        // Count edges where both endpoints are in same team.

        for (auto e : edges) {
            int u = e.first;
            int v = e.second;

            bool inA_u = false, inA_v = false;
            if (u == 1) inA_u = true;
            else if (u == 2) inA_u = false;
            else {
                int bu = id[u];
                inA_u = ((s >> bu) & 1) == 0;
            }

            if (v == 1) inA_v = true;
            else if (v == 2) inA_v = false;
            else {
                int bv = id[v];
                inA_v = ((s >> bv) & 1) == 0;
            }

            if (inA_u == inA_v) {
                if (inA_u) SA++; else SB++;
            }
        }

        long long sum = SA + SB;
        long long diff = llabs(SA - SB);
        if (sum > bestSum) bestSum = sum;
        if (diff < bestDiff) bestDiff = diff;
    }

    // Ensure results fit into signed 64-bit (they obviously do, but we assert)
    ensuref(bestSum >= 0 && bestSum <= (1LL << 60),
            "Computed max sum out of expected 64-bit range");
    ensuref(bestDiff >= 0 && bestDiff <= (1LL << 60),
            "Computed min diff out of expected 64-bit range");
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // t: number of test cases
    int t = inf.readInt(1, 100000, "t");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        // Each test case is preceded by a blank line
        // i.e., exactly one empty line (just '\n')
        string blank = inf.readLine("[^]*", "blank_line");
        ensuref(blank.empty(),
                "Test case %d is not preceded by a blank line", tc);

        // Read n, m
        int n = inf.readInt(2, 200, "n");
        inf.readSpace();
        long long maxM = 1LL * n * (n - 1) / 2;
        int m = inf.readInt(0, (int)maxM, "m");
        inf.readEoln();

        // Read m edges, undirected, u < v, no duplicates, no loops
        set<pair<int,int>> edgesSet;
        vector<pair<int,int>> edges;
        edges.reserve(m);

        for (int i = 0; i < m; ++i) {
            int u = inf.readInt(1, n, "u_i");
            inf.readSpace();
            int v = inf.readInt(1, n, "v_i");
            inf.readEoln();

            ensuref(u < v, "Edge %d must satisfy u_i < v_i, got (%d, %d)",
                    i + 1, u, v);
            ensuref(u != v, "Self-loop detected at edge %d: (%d, %d)",
                    i + 1, u, v);

            pair<int,int> e = {u, v};
            ensuref(!edgesSet.count(e),
                    "Multiple edges detected at edge %d: (%d, %d)",
                    i + 1, u, v);
            edgesSet.insert(e);
            edges.push_back(e);
        }

        // Global sanity: ensure 1 and 2 exist by constraints already (1..n).

        // Optional global property checks (bounds and feasibility)
        checkAnswers(n, edges);
    }

    inf.readEof();
}
