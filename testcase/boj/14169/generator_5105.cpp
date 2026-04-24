#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int INF = 1e9;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter: max coordinate grid size
    int MAXC = rnd.next(3, 10);

    int N;
    vector<pair<ll,ll>> posts;
    ll xL, yL, xB, yB;
    auto computeMirrors = [&](vector<pair<ll,ll>>& pts, ll xL, ll yL, ll xB, ll yB) {
        int M = pts.size();
        // nodes: 0=start, 1..M=posts, M+1=barn
        int tot = M + 2;
        vector<pair<ll,ll>> nodes(tot);
        nodes[0] = {xL, yL};
        for (int i = 0; i < M; i++) nodes[i+1] = pts[i];
        nodes[M+1] = {xB, yB};
        // adjacency list
        vector<vector<int>> adj(tot);
        for (int i = 0; i < tot; i++) {
            for (int j = 0; j < tot; j++) {
                if (i == j) continue;
                if (nodes[i].first == nodes[j].first ||
                    nodes[i].second == nodes[j].second) {
                    adj[i].push_back(j);
                }
            }
        }
        // dist[node][dir], dir=0 horizontal, 1 vertical
        vector<array<int,2>> dist(tot, {INF, INF});
        deque<pair<int,int>> dq;
        // start in both directions, 0 mirrors used
        dist[0][0] = dist[0][1] = 0;
        dq.emplace_back(0, 0);
        dq.emplace_back(0, 1);
        while (!dq.empty()) {
            auto [u, dir] = dq.front(); dq.pop_front();
            int d = dist[u][dir];
            // mirror flip at a post
            if (u >= 1 && u <= M) {
                int nd = d + 1;
                if (nd < dist[u][1-dir]) {
                    dist[u][1-dir] = nd;
                    dq.emplace_back(u, 1-dir);
                }
            }
            // propagate in same direction to neighbors
            for (int v : adj[u]) {
                // check alignment matches dir
                if (dir == 0 && nodes[u].second != nodes[v].second) continue;
                if (dir == 1 && nodes[u].first != nodes[v].first) continue;
                if (d < dist[v][dir]) {
                    dist[v][dir] = d;
                    dq.emplace_front(v, dir);
                }
            }
        }
        int ans = min(dist[M+1][0], dist[M+1][1]);
        return (ans >= INF ? -1 : ans);
    };

    // generate until diversity: mostly reachable, sometimes unreachable
    while (true) {
        N = rnd.next(1, 7);
        // sample laser and barn
        auto samplePt = [&](){
            return make_pair<ll,ll>(rnd.next(0LL, (ll)MAXC-1), rnd.next(0LL, (ll)MAXC-1));
        };
        // ensure start != barn
        do {
            tie(xL, yL) = samplePt();
            tie(xB, yB) = samplePt();
        } while (xL == xB && yL == yB);
        // sample distinct posts
        posts.clear();
        set<pair<ll,ll>> seen;
        seen.insert({xL,yL});
        seen.insert({xB,yB});
        while ((int)posts.size() < N) {
            auto p = samplePt();
            if (seen.insert(p).second) posts.push_back(p);
        }
        int res = computeMirrors(posts, xL, yL, xB, yB);
        bool ok = (res != -1);
        double p = rnd.next();
        if ((ok && p < 0.8) || (!ok && p < 0.2)) {
            break;
        }
    }

    // output
    println(N, xL, yL, xB, yB);
    for (auto &p : posts) {
        println(p.first, p.second);
    }
    return 0;
}
