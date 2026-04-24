#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Small graph size
    int N = rnd.next(2, 10);
    int Emax = N * (N - 1) / 2;
    // Total queries M, keep it small but diverse
    int M = rnd.next(N, min(Emax * 2, 20));

    // Enumerate all possible undirected edges (1-based)
    vector<pair<int,int>> allEdges;
    for (int i = 1; i <= N; i++) {
        for (int j = i + 1; j <= N; j++) {
            allEdges.emplace_back(i, j);
        }
    }
    int totalEdges = (int)allEdges.size();

    // Maintain which edges can be added or removed
    vector<int> canAdd, canRemove;
    canAdd.reserve(totalEdges);
    for (int i = 0; i < totalEdges; i++) {
        canAdd.push_back(i);
    }

    // Hyper-parameters for operation probabilities
    double wAdd = rnd.next();
    double wRemove = rnd.next();
    double wQuery = rnd.next();
    double sumW = wAdd + wRemove + wQuery;
    double pAdd = wAdd / sumW;
    double pRemove = wRemove / sumW;
    // pQuery = 1 - pAdd - pRemove

    struct Q { int t, a, b; };
    vector<Q> queries;
    queries.reserve(M);

    for (int i = 0; i < M; i++) {
        bool canA = !canAdd.empty();
        bool canR = !canRemove.empty();
        double x = rnd.next();
        int type;
        if (canA && canR) {
            if (x < pAdd) type = 1;
            else if (x < pAdd + pRemove) type = 2;
            else type = 3;
        } else if (canA) {
            // only add or query
            double pa = wAdd / (wAdd + wQuery);
            type = (x < pa ? 1 : 3);
        } else if (canR) {
            // only remove or query
            double pr = wRemove / (wRemove + wQuery);
            type = (x < pr ? 2 : 3);
        } else {
            // only queries possible
            type = 3;
        }

        if (type == 1) {
            // add an edge
            int idx = rnd.next(0, (int)canAdd.size() - 1);
            int eid = canAdd[idx];
            canAdd.erase(canAdd.begin() + idx);
            canRemove.push_back(eid);
            auto [u, v] = allEdges[eid];
            queries.push_back({1, u, v});
        }
        else if (type == 2) {
            // remove an edge
            int idx = rnd.next(0, (int)canRemove.size() - 1);
            int eid = canRemove[idx];
            canRemove.erase(canRemove.begin() + idx);
            canAdd.push_back(eid);
            auto [u, v] = allEdges[eid];
            queries.push_back({2, u, v});
        }
        else {
            // connectivity query
            int u = rnd.next(1, N);
            int v = rnd.next(1, N);
            while (v == u) v = rnd.next(1, N);
            queries.push_back({3, u, v});
        }
    }

    // Output
    println(N, M);
    for (auto &q : queries) {
        println(q.t, q.a, q.b);
    }

    return 0;
}
