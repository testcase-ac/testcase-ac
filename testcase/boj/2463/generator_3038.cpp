#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of nodes
    int N = rnd.next(2, 10);
    int maxEdges = N * (N - 1) / 2;
    // Sample M with bias
    vector<int> tset = {-3, -2, -1, 1, 2, 3};
    int t = rnd.any(tset);
    int m0 = rnd.wnext(maxEdges + 1, t);
    int M = min(maxEdges, max(1, m0));
    // Decide if we enforce connectivity (only if enough edges)
    bool ensureConn = (rnd.next() < 0.5) && (M >= N - 1);
    vector<pair<int,int>> TE, OE, allEdges;
    // Build all possible edges
    for (int i = 1; i <= N; i++) {
        for (int j = i+1; j <= N; j++) {
            allEdges.emplace_back(i, j);
        }
    }
    if (ensureConn) {
        // Build a random spanning tree first
        vector<int> nodes(N);
        for (int i = 0; i < N; i++) nodes[i] = i+1;
        shuffle(nodes.begin(), nodes.end());
        for (int i = 0; i < N-1; i++) {
            TE.emplace_back(nodes[i], nodes[i+1]);
        }
        // Remove tree edges from allEdges
        vector<pair<int,int>> tmp;
        for (auto &e : allEdges) {
            bool isTree = false;
            for (auto &te : TE)
                if ((e.first==te.first && e.second==te.second) ||
                    (e.first==te.second && e.second==te.first)) {
                    isTree = true; break;
                }
            if (!isTree) tmp.push_back(e);
        }
        allEdges.swap(tmp);
        // Pick remaining OE
        shuffle(allEdges.begin(), allEdges.end());
        int need = M - (int)TE.size();
        for (int i = 0; i < need; i++) {
            OE.push_back(allEdges[i]);
        }
    } else {
        // Just pick any M edges
        shuffle(allEdges.begin(), allEdges.end());
        for (int i = 0; i < M; i++) {
            OE.push_back(allEdges[i]);
        }
    }
    // Combine final edge list
    vector<pair<int,int>> finalEdges;
    if (ensureConn) {
        finalEdges = TE;
        finalEdges.insert(finalEdges.end(), OE.begin(), OE.end());
    } else {
        finalEdges = OE;
    }
    // Generate a pool of distinct weights
    int wmax = rnd.next(M, M * 5);
    vector<int> wpool(wmax);
    for (int i = 0; i < wmax; i++) wpool[i] = i+1;
    shuffle(wpool.begin(), wpool.end());
    vector<int> W;
    if (!ensureConn) {
        // Just take first M random weights
        for (int i = 0; i < M; i++) W.push_back(wpool[i]);
    } else {
        // Bias tree edges heavy or light
        bool heavyTree = rnd.next() < 0.5;
        // Sort pool and pick best
        sort(wpool.begin(), wpool.end());
        if (heavyTree) {
            // tree edges get largest weights
            for (int i = 0; i < (int)TE.size(); i++)
                W.push_back(wpool[wmax - 1 - i]);
            for (int i = 0; i < (int)OE.size(); i++)
                W.push_back(wpool[i]);
        } else {
            // tree edges get smallest
            for (int i = 0; i < (int)TE.size(); i++)
                W.push_back(wpool[i]);
            for (int i = 0; i < (int)OE.size(); i++)
                W.push_back(wpool[(int)TE.size() + i]);
        }
    }
    // Shuffle final edges with weights together for randomness
    struct E3 { int u,v,w; };
    vector<E3> out;
    for (int i = 0; i < M; i++) {
        out.push_back({finalEdges[i].first, finalEdges[i].second, W[i]});
    }
    shuffle(out.begin(), out.end());
    // Output
    println(N, M);
    for (auto &e : out) {
        println(e.u, e.v, e.w);
    }
    return 0;
}
