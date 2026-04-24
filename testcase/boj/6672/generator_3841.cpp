#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of instances
    int T = rnd.next(1, 5);
    for (int ti = 0; ti < T; ti++) {
        // Number of plants
        int P = rnd.next(2, 10);
        // Prepare edge container and existence matrix
        vector<pair<int,int>> edges;
        vector<vector<char>> used(P, vector<char>(P, 0));

        // Choose graph type: 0=random, 1=tree+extra, 2=disconnected
        int gtype = rnd.next(0, 2);
        if (gtype == 0) {
            // Pure random graph
            int maxE = P*(P-1)/2;
            int M = rnd.next(0, maxE);
            vector<pair<int,int>> cand;
            for (int i = 0; i < P; i++)
                for (int j = i+1; j < P; j++)
                    cand.emplace_back(i, j);
            shuffle(cand.begin(), cand.end());
            for (int i = 0; i < M; i++) {
                edges.push_back(cand[i]);
            }
        }
        else if (gtype == 1) {
            // Generate random tree first
            for (int i = 1; i < P; i++) {
                int p = rnd.next(0, i-1);
                edges.emplace_back(i, p);
                used[i][p] = used[p][i] = 1;
            }
            // Add a few extra edges
            int maxE = P*(P-1)/2 - (P-1);
            int extra = rnd.next(0, max(0, min(maxE, P/2)));
            vector<pair<int,int>> cand;
            for (int i = 0; i < P; i++)
                for (int j = i+1; j < P; j++)
                    if (!used[i][j])
                        cand.emplace_back(i, j);
            shuffle(cand.begin(), cand.end());
            for (int i = 0; i < extra && i < (int)cand.size(); i++) {
                auto e = cand[i];
                edges.push_back(e);
                used[e.first][e.second] = used[e.second][e.first] = 1;
            }
        }
        else {
            // Disconnected graph: random components
            int k = rnd.next(2, min(P, 4));
            vector<int> nodes(P);
            for (int i = 0; i < P; i++) nodes[i] = i;
            shuffle(nodes.begin(), nodes.end());
            // Component sizes
            vector<int> comp_sz(k, 1);
            int rem = P - k;
            for (int i = 0; i < rem; i++) {
                int x = rnd.next(0, k-1);
                comp_sz[x]++;
            }
            // Assign nodes to components
            int idx = 0;
            for (int ci = 0; ci < k; ci++) {
                int sz = comp_sz[ci];
                vector<int> comp_nodes(nodes.begin()+idx, nodes.begin()+idx+sz);
                idx += sz;
                // For each component, choose random edges
                int maxE = sz*(sz-1)/2;
                int Mcomp = rnd.next(0, maxE);
                vector<pair<int,int>> cand;
                for (int i = 0; i < sz; i++)
                    for (int j = i+1; j < sz; j++)
                        cand.emplace_back(comp_nodes[i], comp_nodes[j]);
                shuffle(cand.begin(), cand.end());
                for (int i = 0; i < Mcomp && i < (int)cand.size(); i++) {
                    auto e = cand[i];
                    if (!used[e.first][e.second]) {
                        edges.push_back(e);
                        used[e.first][e.second] = used[e.second][e.first] = 1;
                    }
                }
            }
        }

        // Output this instance
        int M = edges.size();
        println(P, M);
        for (auto &e : edges)
            println(e.first, e.second);
    }
    // Termination line
    println(0, 0);

    return 0;
}
