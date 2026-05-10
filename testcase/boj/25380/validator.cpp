#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N, M, K
    int N = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int M = inf.readInt(1, 100000, "M");
    inf.readSpace();
    int K = inf.readInt(2, N + M, "K");
    inf.readEoln();

    // Read vertical roads a_i
    vector<int> a = inf.readInts(N, -100000, 100000, "a_i");
    inf.readEoln();
    // Check distinctness of a_i
    {
        vector<int> sa = a;
        sort(sa.begin(), sa.end());
        for (int i = 1; i < N; i++) {
            ensuref(sa[i] != sa[i-1],
                    "Duplicate vertical road coordinate a[%d] = %d",
                    i, sa[i]);
        }
    }

    // Read horizontal roads b_j
    vector<int> b = inf.readInts(M, -100000, 100000, "b_j");
    inf.readEoln();
    // Check distinctness of b_j
    {
        vector<int> sb = b;
        sort(sb.begin(), sb.end());
        for (int i = 1; i < M; i++) {
            ensuref(sb[i] != sb[i-1],
                    "Duplicate horizontal road coordinate b[%d] = %d",
                    i, sb[i]);
        }
    }

    // Build lookup sets for fast checking
    unordered_set<int> setA, setB;
    setA.reserve(N * 2);
    setB.reserve(M * 2);
    for (int x : a) setA.insert(x);
    for (int y : b) setB.insert(y);

    // Track police positions to ensure no duplicates
    set<pair<int,int>> police_pos;

    // Read K police positions
    for (int i = 0; i < K; i++) {
        int p = inf.readInt(-100000, 100000, "p_k");
        inf.readSpace();
        int q = inf.readInt(-100000, 100000, "q_k");
        inf.readEoln();

        // Distinct positions
        ensuref(!police_pos.count({p, q}),
                "Duplicate police position at (%d, %d)", p, q);
        police_pos.insert({p, q});

        // Must lie on at least one road
        bool onA = setA.count(p);
        bool onB = setB.count(q);
        ensuref(onA || onB,
                "Police at (%d, %d) is not on any road", p, q);
        // Note: if on both, it's at an intersection and may be assigned to exactly one of them.
    }

    // No extra content
    inf.readEof();
    return 0;
}
