#include "testlib.h"
#include <vector>
#include <set>
#include <queue>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // small sizes
    int N = rnd.next(2, 10);
    int M = rnd.next(N, 2 * N);
    // weights for ops
    int Wlink = rnd.next(0, 10);
    int Wcut = rnd.next(0, 10);
    int Wquery = rnd.next(0, 10);
    if (Wlink + Wcut + Wquery == 0) {
        Wquery = 1;
    }
    // forest state
    vector< set<int> > adj(N);
    vector< pair<int,int> > edges;
    // output header
    println(N, M);
    for (int qi = 0; qi < M; qi++) {
        // compute components by BFS
        vector<int> comp(N, -1);
        int compCnt = 0;
        for (int i = 0; i < N; i++) {
            if (comp[i] == -1) {
                queue<int> q;
                comp[i] = compCnt;
                q.push(i);
                while (!q.empty()) {
                    int u = q.front(); q.pop();
                    for (int v : adj[u]) {
                        if (comp[v] == -1) {
                            comp[v] = compCnt;
                            q.push(v);
                        }
                    }
                }
                compCnt++;
            }
        }
        bool link_possible = (compCnt > 1);
        bool cut_possible = (!edges.empty());
        // build possible ops with weights
        vector<int> ops;
        vector<int> ws;
        if (link_possible && Wlink > 0) {
            ops.push_back(1);
            ws.push_back(Wlink);
        }
        if (cut_possible && Wcut > 0) {
            ops.push_back(2);
            ws.push_back(Wcut);
        }
        if (Wquery > 0) {
            ops.push_back(3);
            ws.push_back(Wquery);
        }
        // ensure at least one op
        if (ops.empty()) {
            ops.push_back(3);
            ws.push_back(1);
        }
        // choose op by weight
        int totalW = 0;
        for (int w : ws) totalW += w;
        int pick = rnd.next(1, totalW);
        int acc = 0, chosen = 3;
        for (size_t i = 0; i < ops.size(); i++) {
            acc += ws[i];
            if (pick <= acc) {
                chosen = ops[i];
                break;
            }
        }
        if (chosen == 1) {
            // link: pick any two nodes in different components
            vector<pair<int,int>> cand;
            for (int i = 0; i < N; i++) {
                for (int j = i+1; j < N; j++) {
                    if (comp[i] != comp[j]) {
                        cand.emplace_back(i, j);
                    }
                }
            }
            auto pr = rnd.any(cand);
            int u = pr.first, v = pr.second;
            adj[u].insert(v);
            adj[v].insert(u);
            edges.emplace_back(u, v);
            println(1, u+1, v+1);
        } else if (chosen == 2) {
            // cut: pick existing edge
            int idx = rnd.next(0, (int)edges.size() - 1);
            auto pr = edges[idx];
            int u = pr.first, v = pr.second;
            adj[u].erase(v);
            adj[v].erase(u);
            edges.erase(edges.begin() + idx);
            println(2, u+1, v+1);
        } else {
            // query
            int u = rnd.next(0, N-1);
            int v = rnd.next(0, N-1);
            while (v == u) v = rnd.next(0, N-1);
            println(3, u+1, v+1);
        }
    }
    return 0;
}
