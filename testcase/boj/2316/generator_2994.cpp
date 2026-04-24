#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of cities
    int N = rnd.next(3, 10);
    // Decide a base number of vertex-disjoint paths between 1 and 2
    int maxK = min(3, N - 2);
    int k = rnd.next(0, maxK);
    // Prepare available intermediate cities
    vector<int> avail;
    for (int i = 3; i <= N; i++) avail.push_back(i);
    shuffle(avail.begin(), avail.end());
    // Build k vertex-disjoint paths
    vector<pair<int,int>> edges;
    for (int i = 0; i < k; i++) {
        int needMin = k - i;
        int maxLen = int(avail.size()) - (needMin - 1);
        int L = rnd.next(1, min(maxLen, 3));
        vector<int> pathNodes(avail.begin(), avail.begin() + L);
        avail.erase(avail.begin(), avail.begin() + L);
        // Connect 1 -> ... -> 2
        edges.emplace_back(1, pathNodes[0]);
        for (int j = 0; j + 1 < L; j++)
            edges.emplace_back(pathNodes[j], pathNodes[j+1]);
        edges.emplace_back(pathNodes.back(), 2);
    }
    // Mark used edges
    vector<vector<bool>> used(N+1, vector<bool>(N+1, false));
    for (auto &e : edges) {
        used[e.first][e.second] = used[e.second][e.first] = true;
    }
    // Candidate extra edges (no duplicates, no direct 1-2)
    vector<pair<int,int>> cand;
    for (int i = 1; i <= N; i++) {
        for (int j = i + 1; j <= N; j++) {
            if (i == 1 && j == 2) continue;
            if (!used[i][j])
                cand.emplace_back(i, j);
        }
    }
    shuffle(cand.begin(), cand.end());
    // Add some extra edges to increase complexity
    int limit = min((int)cand.size(), N);
    int extra;
    if (edges.empty())
        extra = rnd.next(1, limit);
    else
        extra = rnd.next(0, limit);
    for (int i = 0; i < extra; i++) {
        edges.push_back(cand[i]);
    }
    // Final shuffle of edges
    shuffle(edges.begin(), edges.end());
    // Output
    int P = edges.size();
    println(N, P);
    for (auto &e : edges)
        println(e.first, e.second);
    return 0;
}
