#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Small sizes for hand verification
    int N = rnd.next(1, 10);
    int maxEdges = N * (N - 1) / 2;
    bool feasible = rnd.next(0, 1) == 1;

    vector<int> p(N);
    vector<pair<int,int>> edges;
    vector<int> s, e;

    // Prepare list of all unordered pairs
    vector<pair<int,int>> unord;
    for (int u = 1; u <= N; u++) {
        for (int v = u + 1; v <= N; v++) {
            unord.emplace_back(u, v);
        }
    }

    if (feasible) {
        // Feasible instance
        if (N <= 2) {
            // Only trivial feasibles: all p_i = 0, no edges
            p.assign(N, 0);
            edges.clear();
        } else {
            // Generate p summing to zero
            int sum = 0;
            for (int i = 0; i < N - 1; i++) {
                p[i] = rnd.next(-5, 5);
                sum += p[i];
            }
            p[N - 1] = -sum;
            // Build a simple directed cycle covering all nodes
            vector<int> perm(N);
            iota(perm.begin(), perm.end(), 1);
            shuffle(perm.begin(), perm.end());
            for (int i = 0; i < N - 1; i++) {
                edges.emplace_back(perm[i], perm[i+1]);
            }
            edges.emplace_back(perm[N-1], perm[0]);
            // Collect available unordered pairs not in the cycle
            vector<pair<int,int>> available;
            for (auto uv : unord) {
                // check if uv used in cycle (in either direction)
                bool used = false;
                for (auto &e0 : edges) {
                    int a = e0.first, b = e0.second;
                    if ((uv.first == a && uv.second == b) || (uv.first == b && uv.second == a)) {
                        used = true; break;
                    }
                }
                if (!used) available.push_back(uv);
            }
            // Optionally add extras with zero flow
            int maxExtra = min((int)available.size(), N/2);
            int extras = rnd.next(0, maxExtra);
            shuffle(available.begin(), available.end());
            for (int i = 0; i < extras; i++) {
                int u = available[i].first, v = available[i].second;
                if (rnd.next(0,1) == 0) edges.emplace_back(u, v);
                else edges.emplace_back(v, u);
            }
        }
        int M = edges.size();
        // Build lower/upper bounds
        s.resize(M);
        e.resize(M);
        if (N >= 3) {
            // Compute flows on the cycle edges
            int cycleSize = N;
            vector<int> pref(cycleSize);
            // Build prefix sums of p in cycle order
            pref[0] = p[ edges[0].first - 1 ];
            for (int i = 1; i < cycleSize; i++) {
                pref[i] = pref[i-1] + p[ edges[i].first - 1 ];
            }
            // Find minimum prefix to make flows non-negative
            int minpref = *min_element(pref.begin(), pref.end());
            int base = rnd.next(-minpref, -minpref + 5);
            vector<int> flow(M, 0);
            for (int i = 0; i < cycleSize; i++) {
                flow[i] = base + pref[i];
            }
            // Extras have zero flow
            for (int i = cycleSize; i < M; i++) {
                flow[i] = 0;
            }
            // Assign bounds
            for (int i = 0; i < M; i++) {
                int f = flow[i];
                if (i < cycleSize) {
                    s[i] = rnd.next(0, f);
                    e[i] = rnd.next(f, f + rnd.next(0, 5));
                } else {
                    s[i] = 0;
                    e[i] = rnd.next(0, rnd.next(0, 5));
                }
            }
        } else {
            // N <= 2: no edges
            s.clear();
            e.clear();
            M = 0;
        }
        // Output feasible
        println(N, M);
        println(p);
        for (int i = 0; i < (int)edges.size(); i++) {
            println(edges[i].first, edges[i].second, s[i], e[i]);
        }
    } else {
        // Infeasible: violate sum of p == 0
        int sum = 0;
        if (N >= 2) {
            for (int i = 0; i < N - 1; i++) {
                p[i] = rnd.next(-5, 5);
                sum += p[i];
            }
            // pick last so that total sum != 0
            do {
                p[N-1] = rnd.next(-5, 5);
            } while (sum + p[N-1] == 0);
        } else {
            // N == 1, make p[0] != 0
            do {
                p[0] = rnd.next(-5, 5);
            } while (p[0] == 0);
        }
        // Random edges and bounds
        int M = rnd.next(0, maxEdges);
        shuffle(unord.begin(), unord.end());
        edges.clear();
        s.resize(M);
        e.resize(M);
        for (int i = 0; i < M; i++) {
            int u = unord[i].first, v = unord[i].second;
            if (rnd.next(0,1) == 0) edges.emplace_back(u, v);
            else edges.emplace_back(v, u);
            s[i] = rnd.next(0, rnd.next(0, 5));
            e[i] = rnd.next(s[i], s[i] + rnd.next(0, 5));
        }
        // Output infeasible
        println(N, M);
        println(p);
        for (int i = 0; i < M; i++) {
            println(edges[i].first, edges[i].second, s[i], e[i]);
        }
    }

    return 0;
}
