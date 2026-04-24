#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of vertices
    int N = rnd.next(1, 10);

    // Build a random functional graph: each vertex has at most one outgoing edge
    vector<int> out(N+1, 0);
    int edgesCount = rnd.next(0, N);
    vector<int> nodes(N);
    iota(nodes.begin(), nodes.end(), 1);
    shuffle(nodes.begin(), nodes.end());
    vector<int> withEdge(nodes.begin(), nodes.begin() + edgesCount);
    for (int u : withEdge) {
        int v = rnd.next(1, N);
        if (v == u && N > 1) {
            v = (u % N) + 1;
        }
        out[u] = v;
    }

    // Number of queries
    int Q = rnd.next(1, 20);
    double p_removal = rnd.next(); // probability to pick a removal query

    // Maintain list of vertices whose outgoing edge can still be removed
    vector<int> rem_nodes = withEdge;

    // Output the graph
    println(N);
    for (int i = 1; i <= N; i++) {
        printf("%d%c", out[i], i == N ? '\n' : ' ');
    }

    // Output queries
    println(Q);
    for (int i = 0; i < Q; i++) {
        bool doRemove = !rem_nodes.empty() && rnd.next() < p_removal;
        if (doRemove) {
            int idx = rnd.next(0, (int)rem_nodes.size() - 1);
            int u = rem_nodes[idx];
            println(2, u);
            // remove the edge
            rem_nodes.erase(rem_nodes.begin() + idx);
        } else {
            int u = rnd.next(1, N);
            println(1, u);
        }
    }

    return 0;
}
