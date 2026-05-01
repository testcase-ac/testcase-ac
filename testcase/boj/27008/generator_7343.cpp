#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
#include <tuple>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of fields
    int F = rnd.next(2, 15);
    int mid = F / 2;

    // Number of edges: at least a tree, plus up to F extra edges
    int maxEdges = F * (F - 1) / 2;
    int extra = rnd.next(0, F);
    int P = min((F - 1) + extra, maxEdges);

    // Build a random spanning tree
    vector<int> nodes(F);
    iota(nodes.begin(), nodes.end(), 1);
    shuffle(nodes.begin(), nodes.end());
    vector<pair<int,int>> edges;
    for (int i = 1; i < F; i++) {
        int u = nodes[i];
        int v = nodes[rnd.next(0, i - 1)];
        edges.emplace_back(u, v);
    }

    // Prepare all possible remaining edges
    vector<pair<int,int>> candidates;
    for (int i = 1; i <= F; i++)
        for (int j = i + 1; j <= F; j++)
            candidates.emplace_back(i, j);

    // Remove those already in the tree
    auto isTreeEdge = [&](const pair<int,int>& e) {
        for (auto &t : edges)
            if ((t.first == e.first && t.second == e.second) ||
                (t.first == e.second && t.second == e.first))
                return true;
        return false;
    };
    vector<pair<int,int>> rem;
    for (auto &e : candidates)
        if (!isTreeEdge(e))
            rem.push_back(e);

    // Add extra random edges
    shuffle(rem.begin(), rem.end());
    int need = P - (F - 1);
    for (int i = 0; i < need && i < (int)rem.size(); i++)
        edges.push_back(rem[i]);

    // Weight distribution skew parameter
    int skew = rnd.next(-3, 3);

    // Assign weights
    vector<tuple<int,int,int>> finalEdges;
    for (auto &e : edges) {
        int w = rnd.wnext(70000, skew) + 1;  // 1..70000
        finalEdges.emplace_back(e.first, e.second, w);
    }

    // Time limit M hyper-parameter cases
    int M;
    int mcase = rnd.next(0, 2);
    if (mcase == 0)       M = rnd.next(1, 100);
    else if (mcase == 1)  M = rnd.next(1000, 10000);
    else                  M = rnd.next(1, 70000);

    // Number of cows
    int C = rnd.next(1, min(10, F * 2));

    // Cow placement mode: uniform or clustered near/far
    int cmode = rnd.next(0, 2);
    vector<int> cows(C);
    for (int i = 0; i < C; i++) {
        int x;
        if (cmode == 1) {
            // cluster near barn
            if (rnd.next() < 0.7 && mid >= 1) x = rnd.next(1, mid);
            else                             x = rnd.next(max(1, mid+1), F);
        } else if (cmode == 2) {
            // cluster far
            if (rnd.next() < 0.7)            x = rnd.next(max(1, mid+1), F);
            else                             x = rnd.next(1, mid);
        } else {
            // uniform
            x = rnd.next(1, F);
        }
        cows[i] = x;
    }

    // Output
    println(F, P, C, M);
    for (auto &e : finalEdges)
        println(get<0>(e), get<1>(e), get<2>(e));
    for (int x : cows)
        println(x);

    return 0;
}
