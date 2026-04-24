#include "testlib.h"
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyper-parameter: number of points
    int N = rnd.next(4, 10);
    // Build all possible edges (u<v)
    vector<pair<int,int>> allEdges;
    for (int u = 0; u < N; u++)
        for (int v = u+1; v < N; v++)
            allEdges.emplace_back(u, v);
    // Generate a random spanning tree (edges TEdges)
    vector<pair<int,int>> TEdges;
    for (int i = 1; i < N; i++) {
        int p = rnd.next(0, i-1);
        TEdges.emplace_back(p, i);
    }
    // Shuffle tree edges to randomize order (still acyclic in any prefix)
    shuffle(TEdges.begin(), TEdges.end());
    // Decide case: 0=no cycle, 1=early cycle, 2=late cycle
    int caseType = rnd.next(0, 2);
    vector<pair<int,int>> moves;
    int m;

    if (caseType == 0) {
        // No cycle: take a prefix of tree edges, size m>=3
        m = rnd.next(3, N-1);
        moves.insert(moves.end(), TEdges.begin(), TEdges.begin() + m);
    }
    else if (caseType == 1) {
        // Early cycle: create a simple cycle on C nodes
        int C = rnd.next(3, N);
        // pick C distinct nodes
        vector<int> nodes(N);
        for (int i = 0; i < N; i++) nodes[i] = i;
        shuffle(nodes.begin(), nodes.end());
        nodes.resize(C);
        // cycle edges in order
        vector<pair<int,int>> cycleEdges;
        for (int i = 0; i < C; i++) {
            int u = nodes[i], v = nodes[(i+1)%C];
            if (u > v) swap(u, v);
            cycleEdges.emplace_back(u, v);
        }
        // number of moves: at least C, up to C+5
        int maxExtra = min((int)allEdges.size(), C + 5);
        m = rnd.next(C, maxExtra);
        // first C moves are the cycle edges
        moves = cycleEdges;
        // mark used
        vector<vector<bool>> used(N, vector<bool>(N, false));
        for (auto &e : moves) used[e.first][e.second] = true;
        // collect rest edges
        vector<pair<int,int>> rest;
        for (auto &e : allEdges)
            if (!used[e.first][e.second])
                rest.push_back(e);
        shuffle(rest.begin(), rest.end());
        // append until m
        for (int i = 0; (int)moves.size() < m && i < (int)rest.size(); i++)
            moves.push_back(rest[i]);
    }
    else {
        // Late cycle: tree edges then one extra to close a cycle at step N
        // mark tree edges
        vector<vector<bool>> used(N, vector<bool>(N, false));
        for (auto &e : TEdges) {
            int u=e.first, v=e.second;
            if (u>v) swap(u,v);
            used[u][v] = true;
        }
        // pick one extra edge not in tree
        vector<pair<int,int>> rest;
        for (auto &e : allEdges)
            if (!used[e.first][e.second])
                rest.push_back(e);
        shuffle(rest.begin(), rest.end());
        pair<int,int> extra = rest[0];
        // number of moves: at least N (tree N-1 + extra), up to that +5
        int K = N;
        int maxExtra = min((int)allEdges.size(), K + 5);
        m = rnd.next(K, maxExtra);
        // moves: all tree edges, then extra, then more if needed
        moves = TEdges;
        moves.push_back(extra);
        // mark used
        used[extra.first][extra.second] = true;
        // collect rest for further extra moves
        vector<pair<int,int>> rest2;
        for (auto &e : allEdges)
            if (!used[e.first][e.second])
                rest2.push_back(e);
        shuffle(rest2.begin(), rest2.end());
        for (int i = 0; (int)moves.size() < m && i < (int)rest2.size(); i++)
            moves.push_back(rest2[i]);
    }

    // Output
    println(N, m);
    for (auto &e : moves)
        println(e.first, e.second);

    return 0;
}
