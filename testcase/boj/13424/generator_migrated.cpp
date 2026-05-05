#include "testlib.h"
#include <vector>
#include <algorithm>
#include <utility>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int T = rnd.next(3, 6);
    println(T);
    for (int tc = 0; tc < T; tc++) {
        // Number of rooms
        int N = rnd.next(2, 10);
        int maxEdges = N * (N - 1) / 2;
        double density = rnd.next(0.0, 1.0);
        int midEdges = maxEdges / 2;
        if (midEdges < N - 1) midEdges = N - 1;
        int M;
        if (density < 0.3) {
            M = N - 1;
        } else if (density < 0.7) {
            M = rnd.next(N - 1, midEdges);
        } else {
            M = rnd.next(midEdges, maxEdges);
        }
        // Build a random spanning tree
        vector<vector<bool>> used(N+1, vector<bool>(N+1, false));
        vector<int> nodes(N);
        for (int i = 0; i < N; i++) nodes[i] = i+1;
        shuffle(nodes.begin(), nodes.end());
        vector<pair<int,int>> treeEdges;
        for (int i = 1; i < N; i++) {
            int u = nodes[i];
            int v = nodes[rnd.next(0, i-1)];
            int a = min(u, v), b = max(u, v);
            used[a][b] = true;
            treeEdges.emplace_back(u, v);
        }
        // Collect remaining edges
        vector<pair<int,int>> avail;
        for (int i = 1; i <= N; i++) {
            for (int j = i+1; j <= N; j++) {
                if (!used[i][j]) avail.emplace_back(i, j);
            }
        }
        shuffle(avail.begin(), avail.end());
        int extra = M - (N - 1);
        vector<pair<int,int>> extraEdges(avail.begin(), avail.begin() + extra);
        // Choose weight max
        vector<int> wchoices = {10, 1000};
        int wmax = rnd.any(wchoices);
        // Combine edges with weights
        vector< tuple<int,int,int> > edges;
        for (auto &e : treeEdges) {
            int w = rnd.next(1, wmax);
            edges.emplace_back(e.first, e.second, w);
        }
        for (auto &e : extraEdges) {
            int w = rnd.next(1, wmax);
            edges.emplace_back(e.first, e.second, w);
        }
        shuffle(edges.begin(), edges.end());
        // Number of friends K
        vector<int> bt = {-2, -1, 0, 1, 2};
        int t = rnd.any(bt);
        int K = rnd.wnext(N, t) + 1; // 1..N
        // Friend positions
        vector<int> pos(N);
        for (int i = 0; i < N; i++) pos[i] = i+1;
        shuffle(pos.begin(), pos.end());
        pos.resize(K);
        sort(pos.begin(), pos.end());
        // Output test case
        println(N, M);
        for (auto &e : edges) {
            int u, v, w;
            tie(u, v, w) = e;
            println(u, v, w);
        }
        println(K);
        println(pos);
    }
    return 0;
}
