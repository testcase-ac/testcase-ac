#include "testlib.h"
#include <vector>
#include <tuple>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of huts (nodes)
    int n = rnd.next(2, 10);
    // All possible edges (i < j)
    vector<pair<int,int>> edgesAll;
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            edgesAll.emplace_back(i, j);
    int M_all = edgesAll.size();

    // Track which edges are present or absent
    vector<int> idxAbsent(M_all), idxPresent;
    for (int i = 0; i < M_all; i++) idxAbsent[i] = i;

    // Number of operations
    int k = rnd.next(n, n * 4);

    // Hyper-parameters for operation distribution
    double pQuery  = rnd.next(0.3, 0.7);           // fraction of queries
    double pAddDel = 1.0 - pQuery;                 // remaining for add/delete
    double pAdd    = rnd.next(0.2, 0.8) * pAddDel; // split between add/delete
    double pDel    = pAddDel - pAdd;

    vector<tuple<int,int,int>> ops;
    for (int step = 0; step < k; step++) {
        // Adjust probabilities if no possible add/delete
        double pa = pAdd, pd = pDel, pq = pQuery;
        if (idxAbsent.empty()) {
            pa = 0;
            double s = pd + pq;
            if (s > 0) { pd /= s; pq /= s; }
            else pq = 1;
        }
        if (idxPresent.empty()) {
            pd = 0;
            double s = pa + pq;
            if (s > 0) { pa /= s; pq /= s; }
            else pq = 1;
        }

        double r = rnd.next();
        if (r < pa) {
            // Add an edge
            int ei = rnd.any(idxAbsent);
            // move ei from absent to present
            idxAbsent.erase(find(idxAbsent.begin(), idxAbsent.end(), ei));
            idxPresent.push_back(ei);
            auto [u, v] = edgesAll[ei];
            ops.emplace_back(1, u, v);
        }
        else if (r < pa + pd) {
            // Delete an edge
            int ei = rnd.any(idxPresent);
            idxPresent.erase(find(idxPresent.begin(), idxPresent.end(), ei));
            idxAbsent.push_back(ei);
            auto [u, v] = edgesAll[ei];
            ops.emplace_back(2, u, v);
        }
        else {
            // Query connectivity
            int u = rnd.next(0, n - 1);
            int v = rnd.next(0, n - 2);
            if (v >= u) v++;
            if (u > v) swap(u, v);
            ops.emplace_back(3, u, v);
        }
    }

    // Output
    println(n, k);
    for (auto &t : ops) {
        int tp, u, v;
        tie(tp, u, v) = t;
        println(tp, u, v);
    }

    return 0;
}
