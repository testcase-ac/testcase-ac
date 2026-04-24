#include "testlib.h"
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of intersections
    int N = rnd.next(2, 10);

    // Choose start S and a guaranteed reachable restaurant destR != S
    int S = rnd.next(1, N);
    int destR = rnd.next(1, N);
    while (destR == S) destR = rnd.next(1, N);

    // Hyper-parameter for path length
    int tL = rnd.next(-2, 2);
    int L = rnd.wnext(N - 1, tL) + 1; // number of edges in guaranteed path

    // Build a simple path from S to destR of length L
    int k = L - 1;
    if (k > N - 2) k = N - 2;
    vector<int> pool;
    for (int i = 1; i <= N; i++) {
        if (i != S && i != destR) pool.push_back(i);
    }
    shuffle(pool.begin(), pool.end());
    vector<int> pathNodes;
    pathNodes.push_back(S);
    for (int i = 0; i < k; i++) pathNodes.push_back(pool[i]);
    pathNodes.push_back(destR);

    vector<pair<int,int>> pathEdges;
    set<long long> pathSet;
    for (int i = 0; i + 1 < (int)pathNodes.size(); i++) {
        int u = pathNodes[i], v = pathNodes[i+1];
        pathEdges.emplace_back(u, v);
        pathSet.insert((long long)u * (N+1) + v);
    }

    // Build the rest of possible directed edges excluding the path edges
    vector<pair<int,int>> remEdges;
    remEdges.reserve(N*(N-1));
    for (int u = 1; u <= N; u++) {
        for (int v = 1; v <= N; v++) {
            if (u == v) continue;
            long long code = (long long)u * (N+1) + v;
            if (pathSet.count(code)) continue;
            remEdges.emplace_back(u, v);
        }
    }

    // Hyper-parameter for total edges M
    int Mmax = N * (N - 1);
    int tM = rnd.next(-2, 2);
    int M = rnd.wnext(Mmax - L + 1, tM) + L;
    if (M > Mmax) M = Mmax;
    int need = M - (int)pathEdges.size();
    shuffle(remEdges.begin(), remEdges.end());
    vector<pair<int,int>> edges = pathEdges;
    for (int i = 0; i < need && i < (int)remEdges.size(); i++) {
        edges.push_back(remEdges[i]);
    }
    shuffle(edges.begin(), edges.end());

    // Hyper-parameter for ATM cash distribution
    int tATM = rnd.next(-3, 3);
    vector<int> atm(N+1);
    for (int i = 1; i <= N; i++) {
        atm[i] = rnd.wnext(4001, tATM);
    }

    // Hyper-parameter for number of restaurants P
    int tP = rnd.next(-2, 2);
    int P = rnd.wnext(N, tP) + 1;
    if (P > N) P = N;
    vector<int> others;
    for (int i = 1; i <= N; i++) {
        if (i != destR) others.push_back(i);
    }
    shuffle(others.begin(), others.end());
    vector<int> rests;
    rests.push_back(destR);
    for (int i = 0; i < P - 1 && i < (int)others.size(); i++) {
        rests.push_back(others[i]);
    }
    shuffle(rests.begin(), rests.end());

    // Output
    println(N, M);
    for (auto &e : edges) println(e.first, e.second);
    for (int i = 1; i <= N; i++) println(atm[i]);
    println(S, P);
    println(rests);

    return 0;
}
