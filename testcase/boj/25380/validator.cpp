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

    // Build lookup maps for fast road membership and assignment checks.
    unordered_map<int, int> indexA, indexB;
    indexA.reserve(N * 2);
    indexB.reserve(M * 2);
    for (int i = 0; i < N; ++i) indexA[a[i]] = i;
    for (int i = 0; i < M; ++i) indexB[b[i]] = N + i;

    // Track police positions to ensure no duplicates
    set<pair<int,int>> police_pos;
    vector<vector<int>> candidate_roads(K);

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
        auto itA = indexA.find(p);
        auto itB = indexB.find(q);
        if (itA != indexA.end()) candidate_roads[i].push_back(itA->second);
        if (itB != indexB.end()) candidate_roads[i].push_back(itB->second);
        ensuref(!candidate_roads[i].empty(),
                "Police at (%d, %d) is not on any road", p, q);
        // Note: if on both, it's at an intersection and may be assigned to exactly one of them.
    }

    vector<int> match_road(N + M, -1), match_police(K, -1), dist(K);

    auto bfs = [&]() {
        queue<int> q;
        for (int i = 0; i < K; ++i) {
            if (match_police[i] == -1) {
                dist[i] = 0;
                q.push(i);
            } else {
                dist[i] = -1;
            }
        }

        bool found = false;
        while (!q.empty()) {
            int police = q.front();
            q.pop();
            for (int road : candidate_roads[police]) {
                int next = match_road[road];
                if (next == -1) {
                    found = true;
                } else if (dist[next] == -1) {
                    dist[next] = dist[police] + 1;
                    q.push(next);
                }
            }
        }
        return found;
    };

    auto dfs = [&](auto&& self, int police) -> bool {
        for (int road : candidate_roads[police]) {
            int next = match_road[road];
            if (next == -1 || (dist[next] == dist[police] + 1 && self(self, next))) {
                match_police[police] = road;
                match_road[road] = police;
                return true;
            }
        }
        dist[police] = -1;
        return false;
    };

    int matched = 0;
    while (bfs()) {
        for (int i = 0; i < K; ++i) {
            if (match_police[i] == -1 && dfs(dfs, i)) {
                ++matched;
            }
        }
    }
    ensuref(matched == K, "Police positions cannot be assigned to distinct roads");

    // No extra content
    inf.readEof();
    return 0;
}
